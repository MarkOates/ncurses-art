#include <OrigamiMommyText.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <ncurses_art/Element/Frame.hpp>

#include <ncurses.h>
#include <locale.h>

#include <unistd.h>


#include <sstream>


int score = 0;
int player_x = 40;
int player_y = 40;

std::string get_score_str()
{
   std::stringstream ss;
   ss << score;
   return ss.str();
}


void initialize()
{
   setlocale(LC_ALL, "");
   initscr();
   cbreak();
   //start_color();

   noecho();
   curs_set(0);

   nodelay(stdscr, true);
}

void shutdown()
{
   curs_set(1);
   endwin();
}

void you_draw()
{
   Text(std::string("Standard Text here."), player_x, player_y).draw();

   Frame(5, 5, 100, 20).draw();
   OrigamiMommyText(std::string(" === This is the text I hope to render === "), 8, 7).draw();
}


void draw()
{
   you_draw();
   refresh();
}


#include <iostream>

int main(int argc, char **argv)
{
   initialize();
   //std::cout << "HI!" << std::endl;
   //usleep(2000000);


   draw();

   //mvaddnstr(10, 10, "This workd?", 20);

   usleep(2000000);

   shutdown();
   return 0;
}

