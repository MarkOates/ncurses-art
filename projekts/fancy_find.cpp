#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#define COMMAND_REBUILD_MENU "rebuild_menu"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"
#define COMMAND_SWITCH_TO_INPUT_MODE "COMMAND_SWITCH_TO_INPUT_MODE"
#define COMMAND_SWITCH_TO_NORMAL_MODE "COMMAND_SWITCH_TO_NORMAL_MODE"

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

   std::string get_command()
   {
      std::stringstream ss;
      ss << "git grep -n --untracked --heading --break \"" << search_text << "\"";
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


// trim from start
std::string ltrim(std::string &s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   return s;
}

// trim from end
std::string rtrim(std::string &s) {
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// trim from both ends
std::string trim(std::string s)
{
   //return ltrim(rtrim(s));
   //return ltrim(rtrim(s));
   std::string s1 = s;
   std::string s2 = rtrim(s1);
   std::string s3 = ltrim(s2);
   return s3;
}


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

   return false;
}


bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(20, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000), 0);
      //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      init_color(22, 0, (int)(96.0/255.0*1000), (int)(128.0/255.0*1000));
      //init_color(23, (int)(175.0/255.0*1000), 0, (int)(96.0/255.0*1000));
      init_color(24, 0, 0, 0);
      init_pair(22, COLOR_BLACK, 22);
      //init_pair(2, COLOR_BLACK, 20);
      //init_pair(3, COLOR_BLACK, 21);
      //init_pair(4, 24, 22);
      //init_pair(5, COLOR_MAGENTA, 23);

      //create_menu("text").set_styles(COLOR_PAIR(22));
      create_menu("main_menu").set_styles(COLOR_PAIR(22));
      create_text("input_mode_text", 2, 2).set_styles(COLOR_PAIR(22));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      emit_event(COMMAND_REBUILD_MENU);
      emit_event(COMMAND_SWITCH_TO_NORMAL_MODE);
      emit_event(MOVE_CURSOR_DOWN);
   }
   else if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      std::string trimmed = trim(menu.current_selection());
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == COMMAND_SWITCH_TO_INPUT_MODE)
   {
      state_manager.set_state(STATE_INPUT);
      Text &text = find_text("input_mode_text");
      text.set_text(STATE_INPUT);
   }
   else if (e == COMMAND_SWITCH_TO_NORMAL_MODE)
   {
      state_manager.set_state(STATE_NORMAL);
      Text &text = find_text("input_mode_text");
      text.set_text(STATE_NORMAL);
   }
   //if (e == COPY_GIT_ADD_PATCH_COMMAND)
   //{
      //Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //std::stringstream command;
      //command << "printf \"git add --patch " << git_status_line_deducer.parse_filename() << "\" | pbcopy";
      //system(command.str().c_str());
   //}
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
      std::stringstream ss;
      GitGrepCommand git_grep_command(args[1]);
      ss << git_grep_command.get_command() << " > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      std::string txt = get_file_contents();
      std::vector<std::string> tokens = split_string(txt, "\n");
      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(COLS/4);
      menu.set_y(5);
   }
   return true;
}

