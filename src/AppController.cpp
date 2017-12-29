#include <ncurses_art/AppController.h>

#include <ncurses_art/Screen.h>
#include <ncurses_art/HeaderBar.h>
#include <ncurses_art/EventTypes.h>
#include <ncurses_art/Menu.h>
#include <ncurses_art/Text.h>
#include <ncurses.h>
#include <stdexcept>
#include <sstream>
#include <unistd.h>

#include <string>
#include <fstream>
#include <streambuf>

const int AppController::DEFAULT_USLEEP_DELAY = 10000;

AppController::AppController()
   : initialized(false)
   , screen()
   , event_queue()
   , usleep_delay(DEFAULT_USLEEP_DELAY)
   , program_aborted(false)
{
}

AppController::~AppController()
{
}

void AppController::initialize()
{
   if (initialized) return;

   screen.initialize();
   initialized = true;
}

void AppController::run_loop()
{
   validate_init();

   nodelay(stdscr, true);

   init_color(COLOR_RED, 1000, 0, 0);
   init_color(COLOR_BLACK, 80, 0, 0);
   init_color(20, 0, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000));

   init_pair(1, 20, COLOR_BLACK);
   init_pair(2, 20, COLOR_BLACK);

   std::string title_text = "Projekt";
   std::string body_text = "[Body text goes here]";

   Menu menu(10.0f, 10.0f, {
         "set_title_text_1",
         "set_title_text_2",
         "system_command",
         "create_new_file",
         "curl_command",
         "open_browser_window",
         "run_tests",
         "read_file",
         "view_git_status",
         "show_git_log",
         "show_git_diff",
         "this_projekt_pid",
         "this_projekt_standard_input",
         "this_projekt_standard_error",
         EVENT_ABORT_PROGRAM,
      });

   do
   {
      switch (getch())
      {
      case 'j':
         event_queue.append_event(EVENT_MOVE_CURSOR_DOWN);
         break;
      case 'k':
         event_queue.append_event(EVENT_MOVE_CURSOR_UP);
         break;
      case 'l':
         event_queue.append_event("show_git_log");
         break;
      case 's':
         event_queue.append_event("view_git_status");
         break;
      case 10:
         event_queue.append_event(EVENT_CHOOSE_CURRENT_MENU_ITEM);
         break;
      case 'q':
         event_queue.append_event(EVENT_ABORT_PROGRAM);
         break;
      }

      while (!event_queue.is_empty())
      {
         std::string event = event_queue.pop_event();

         if (event == EVENT_ABORT_PROGRAM) abort_program();
         else if (event == EVENT_MOVE_CURSOR_DOWN) menu.move_cursor_down();
         else if (event == EVENT_MOVE_CURSOR_UP) menu.move_cursor_up();
         else if (event == EVENT_CHOOSE_CURRENT_MENU_ITEM) event_queue.append_event(menu.current_selection());
         else if (event == "set_title_text_1") title_text = "Welcome to the Jungle!";
         else if (event == "set_title_text_2") title_text = "Ncurses is Amazing!!";
         else if (event == "system_command") system("echo \"Hello Mark\"");
         else if (event == "create_new_file") system("echo \"This is the file contents\">\"newfile.txt\"");
         else if (event == "this_projekt_pid")
         {
            system("ps -A | grep -m1 ncurses | awk '{print $1}' > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "this_projekt_standard_input")
         {
            system("ps -A | grep -m1 ncurses | awk '{print \"proc/\"$1\"/fd/0\"}' > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "this_projekt_standard_error")
         {
            system("ps -A | grep -m1 ncurses | awk '{print \"proc/\"$1\"/fd/1\"}' > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "curl_command")
         {
            system("curl -s \"https://jsonplaceholder.typicode.com/users\" > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "run_tests")
         {
            system("bin/test_runner > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "open_browser_window")
         {
            system("open https://www.allegro.cc");
         }
         else if (event == "view_git_status")
         {
            system("git status > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "show_git_diff")
         {
            system("git diff > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "show_git_log")
         {
            system("git log --pretty=tformat:'\''%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -6 > \"output.txt\"");
            event_queue.append_event("read_file");
         }
         else if (event == "read_file")
         {
            std::ifstream t("output.txt");
            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            body_text = str;
         }
         else throw std::runtime_error(std::string("unrecognized event ") + event);
      }

      erase();

      HeaderBar header_bar;
      header_bar.draw();

      Text text(title_text, COLS/2, LINES/3, 0.5);
      text.color(2).underline().draw();

      Text text2(body_text, 0, LINES/2);
      text2.draw();

      menu.draw();

      usleep(usleep_delay);
   }
   while (!program_aborted);
}

void AppController::validate_init()
{
   if (!initialized) throw std::runtime_error("AppController must be initialized before using functionality");
}

void AppController::abort_program()
{
   validate_init();
   program_aborted = true;
}
