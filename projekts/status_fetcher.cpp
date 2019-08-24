#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"

void initialize()
{
   mappings['j'] = MOVE_CURSOR_DOWN;
   mappings['k'] = MOVE_CURSOR_UP;
   mappings['h'] = MOVE_CURSOR_LEFT;
   mappings['l'] = MOVE_CURSOR_RIGHT;

   //std::string repo = args[0];
   std::string repo = "ncurses-art";

   events[INITIALIZE_SCENE] = []{
   };
   events[MOVE_CURSOR_UP] = []{
   };
   events[MOVE_CURSOR_DOWN] = []{
   };
   events[MOVE_CURSOR_LEFT] = []{
   };
   events[MOVE_CURSOR_RIGHT] = []{
   };

   emit_event(INITIALIZE_SCENE);
}

