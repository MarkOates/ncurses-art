#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#include <algorithm> // for std::find_if

#define COMMAND_REBUILD_MENU "rebuild_menu"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"
#define COMMAND_SWITCH_TO_INPUT_MODE "COMMAND_SWITCH_TO_INPUT_MODE"
#define COMMAND_SWITCH_TO_NORMAL_MODE "COMMAND_SWITCH_TO_NORMAL_MODE"
#define INPUT_BUFFER_CHANGED "INPUT_BUFFER_CHANGED"

class GitGrepCommand
{
private:
   std::string search_text;

public:
   GitGrepCommand(std::string search_text)
   : search_text(search_text)
   {
   }
   ~GitGrepCommand() {}

   bool has_search_text()
   {
      return !search_text.empty();
   }

   std::string get_command()
   {
      std::stringstream ss;
      ss << "git grep -n --untracked --heading --break \"" << search_text << "\" \":(exclude)./documentation/*\"";
      return ss.str();
   }
};


class GitGrepLineDeducer
{
private:
   GitGrepCommand *git_grep_command;
   std::string line;

public:
   GitGrepLineDeducer(GitGrepCommand *git_grep_command, std::string line)
      : git_grep_command(git_grep_command)
      , line(line)
   {
   }
   ~GitGrepLineDeducer() {}

   std::string get_filename()
   {
      static std::string filename = "";
      return "";
   }
   std::string get_line_number()
   {
      static std::string line_number = "";
      return "";
   }
};


class StateManager
{
private:
   std::string state;

public:
   StateManager(std::string state="")
      : state(state)
   {}
   ~StateManager()
   {}

   void set_state(std::string state)
   {
      this->state = state;
   }
   std::string get_state()
   {
      return state;
   }
   bool is_state(std::string state)
   {
      return this->state == state;
   }
};


std::string STATE_NORMAL = "normal";
std::string STATE_INPUT = "input";


StateManager state_manager;


#include <Blast/String/Trimmer.hpp>


class InputToActionEmitterInterface
{
protected:
   char input_ch;

public:
   InputToActionEmitterInterface(char input_ch) : input_ch(input_ch) {}
   virtual ~InputToActionEmitterInterface() {}
   virtual bool emit() = 0;
};


class NormalModeInputToAction : private InputToActionEmitterInterface
{
public:
   NormalModeInputToAction(char input_ch)
      : InputToActionEmitterInterface(input_ch)
   {}

   virtual bool emit() override
   {
      switch(input_ch)
      {
         case 'j': emit_event(MOVE_CURSOR_DOWN); return true; break;
         case 'k': emit_event(MOVE_CURSOR_UP); return true; break;
         case 'q': emit_event(EVENT_ABORT_PROGRAM); return true; break;
         case 'y': emit_event(YANK_SELECTED_TEXT); return true; break;
         default: return true; break;
      }

      return false;
   }
};


class GlobalStateSwitcherInputToAction : private InputToActionEmitterInterface
{
private:
   StateManager *state_manager;

public:
   GlobalStateSwitcherInputToAction(char input_ch, StateManager *state_manager)
      : InputToActionEmitterInterface(input_ch)
      , state_manager(state_manager)
   {}

   virtual bool emit() override
   {
      switch(input_ch)
      {
         case '\n':
            // Assume there are only two possible states
            if (state_manager->is_state(STATE_NORMAL)) emit_event(COMMAND_SWITCH_TO_INPUT_MODE);
            else if (state_manager->is_state(STATE_INPUT)) emit_event(COMMAND_SWITCH_TO_NORMAL_MODE);
            return true;
            break;
         default: break;
      }

      return false;
   }
};


class InputBuffer
{
private:
   std::string buffer;

public:
   InputBuffer()
      : buffer("")
   {}

   void set_buffer_text(std::string text)
   {
      buffer = text;
   }
   std::string get_buffer_text()
   {
      return buffer;
   }
   bool empty() { return buffer.empty(); }
   bool append(char ch) { buffer.append(1, ch); return true; }
   void pop_back()
   {
      if (buffer.empty()) throw std::runtime_error("cannot pop_back on an empty buffer");
      buffer.erase(buffer.size() - 1);
   }
};

InputBuffer input_buffer;


class InputBufferInputToAction : private InputToActionEmitterInterface
{
private:
   InputBuffer *input_buffer;

public:
   InputBufferInputToAction(char input_ch, InputBuffer *input_buffer)
      : InputToActionEmitterInterface(input_ch)
      , input_buffer(input_buffer)
   {}

   virtual bool emit() override
   {
      if (!input_buffer) throw std::runtime_error("nil buffer");

      if (input_ch == 127) // backspace
      {
         if (!input_buffer->empty()) input_buffer->pop_back();
         emit_event(INPUT_BUFFER_CHANGED);
         return true;
      }
      else
      {
         input_buffer->append(input_ch);
         emit_event(INPUT_BUFFER_CHANGED);
         return true;
      }
   }
};


Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   GlobalStateSwitcherInputToAction global_state_switcher_input_to_action(ch, &state_manager);
   if (global_state_switcher_input_to_action.emit()) return true;

   if (state_manager.is_state(STATE_NORMAL))
   {
      NormalModeInputToAction normal_mode_input_to_action(ch);
      if (normal_mode_input_to_action.emit()) return true;
   }
   else if (state_manager.is_state(STATE_INPUT))
   {
      InputBufferInputToAction input_buffer_input_to_action(ch, &input_buffer);
      if (input_buffer_input_to_action.emit()) return true;
   }

   return false;
}


bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(20, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000), 0);
      init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      init_color(22, 0, (int)(96.0/255.0*1000), (int)(128.0/255.0*1000));
      init_color(23, (int)(175.0/255.0*1000), 0, (int)(96.0/255.0*1000));
      init_color(24, 0, 0, 0);
      init_pair(22, COLOR_BLACK, 20);
      //init_pair(2, COLOR_BLACK, 20);
      //init_pair(3, COLOR_BLACK, 21);
      //init_pair(4, 24, 22);
      //init_pair(5, COLOR_MAGENTA, 23);

std::stringstream ss;
ss <<
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << std::endl <<
"░░░░░░░█▀▀ █▀▀█ █▀▀▄ █▀▀ █ ░█ ░░█▀▀ ░▀ ░█▀▀▄░█▀▀▄░█▀▀ █▀▀█ ░░░░░░" << std::endl <<
"░░░░░░░█▀▀ █▄▄█ █ ░█ █ ░░█▄▄█ ░░█▀▀ ▀█▀ █ ░█ █ ░█ █▀▀ █▄▄▀ ░░░░░░" << std::endl <<
"░░░░░░░▀ ░ ▀ ░▀ ▀ ░▀ ▀▀▀ ▄▄▄█ ░░▀ ░░▀▀▀ ▀ ░▀ ▀▀▀  ▀▀▀ ▀ ▀▀ ░░░░░░" << std::endl <<
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << std::endl <<
std::endl;

      //create_menu("text").set_styles(COLOR_PAIR(22));
      create_menu("main_menu").set_styles(COLOR_PAIR(22));
      create_text("title", 2, 2).set_styles(COLOR_PAIR(22));
      find_text("title").set_text(ss.str());
      create_text("input_mode_text", 2, 8).set_styles(COLOR_PAIR(22));
      create_text("input_buffer", 2, 10).set_styles(COLOR_PAIR(20));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      if (args.size() <= 1) // no args were provided
      {
         emit_event(COMMAND_REBUILD_MENU);
         emit_event(COMMAND_SWITCH_TO_INPUT_MODE);
         emit_event(MOVE_CURSOR_DOWN);
      }
      else // args were passed on initialization
      {
         std::string initial_args_text = args[1];
         input_buffer.set_buffer_text(initial_args_text);
         emit_event(INPUT_BUFFER_CHANGED);
         emit_event(COMMAND_REBUILD_MENU);
         emit_event(COMMAND_SWITCH_TO_NORMAL_MODE);
         emit_event(MOVE_CURSOR_DOWN);
      }
   }
   else if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == COMMAND_SWITCH_TO_INPUT_MODE)
   {
      state_manager.set_state(STATE_INPUT);
      Text &text = find_text("input_mode_text");
      text.set_text(STATE_INPUT);
      emit_event(COMMAND_REBUILD_MENU);
   }
   else if (e == COMMAND_SWITCH_TO_NORMAL_MODE)
   {
      state_manager.set_state(STATE_NORMAL);
      Text &text = find_text("input_mode_text");
      text.set_text(STATE_NORMAL);
      emit_event(COMMAND_REBUILD_MENU);
   }
   //if (e == COPY_GIT_ADD_PATCH_COMMAND)
   //{
      //Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //std::stringstream command;
      //command << "printf \"git add --patch " << git_status_line_deducer.parse_filename() << "\" | pbcopy";
      //system(command.str().c_str());
   //}
   else if (e == INPUT_BUFFER_CHANGED)
   {
      Text &text = find_text("input_buffer");
      text.set_text(input_buffer.get_buffer_text());
   }
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //int next_file_line = git_status_line_deducer.find_next_file_line();
      //if (next_file_line != -1) menu.set_cursor_pos(next_file_line);
      //else menu.move_cursor_down();
      menu.set_y(menu.get_y()-1);
      menu.move_cursor_down();
      //emit_event(REFRESH_TEXT_DISPLAY);
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //int previous_file_line = git_status_line_deducer.find_previous_file_line();
      //if (previous_file_line != -1) menu.set_cursor_pos(previous_file_line);
      //else menu.move_cursor_up();
      menu.set_y(menu.get_y()+1);
      menu.move_cursor_up();
      //emit_event(REFRESH_TEXT_DISPLAY);
   }
   else if (e == COMMAND_REBUILD_MENU)
   {
      GitGrepCommand git_grep_command(input_buffer.get_buffer_text());
      std::vector<std::string> tokens;
      if (git_grep_command.has_search_text())
      {
         std::string command = git_grep_command.get_command();
         std::stringstream ss;
         ss << command << " > \"" << TMP_OUTFILE << "\"";
         system(ss.str().c_str());
         std::string txt = get_file_contents();
         tokens = split_string(txt, "\n");
      }
      else
      {
         tokens = split_string("[empty search text]", "\n");
      }
      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(COLS/4);
      menu.set_y(11);
   }
   return true;
}

