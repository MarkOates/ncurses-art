#include "Projekt2.h"

#define SET_TEXT "set_text"

#define CREATE_NOTE_AT_CURSOR "CREATE_NOTE_AT_CURSOR"
#define REMOVE_NOTE_AT_CURSOR "REMOVE_NOTE_AT_CURSOR"
#define CREATE_STAFF_AT_CURSOR "CREATE_STAFF_AT_CURSOR"
#define REMOVE_STAFF_AT_CURSOR "REMOVE_STAFF_AT_CURSOR"
#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define MOVE_CAMERA_UP "MOVE_CAMERA_UP"
#define MOVE_CAMERA_DOWN "MOVE_CAMERA_DOWN"
#define MOVE_CAMERA_LEFT "MOVE_CAMERA_LEFT"
#define MOVE_CAMERA_RIGHT "MOVE_CAMERA_RIGHT"
#define SAVE_SCORE "SAVE_SCORE"
#define LOAD_SCORE "LOAD_SCORE"

class Cursor;
class Score;

void render(Score &score, Cursor &cursor)
{
}

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_text("text", 10, 20);
   create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   mappings['t'] = SET_TEXT;

   mappings['!'] = CREATE_NOTE_AT_CURSOR;
   mappings['!'] = REMOVE_NOTE_AT_CURSOR;
   mappings['!'] = CREATE_STAFF_AT_CURSOR;
   mappings['!'] = REMOVE_STAFF_AT_CURSOR;

   mappings['k'] = MOVE_CURSOR_UP;
   mappings['j'] = MOVE_CURSOR_DOWN;
   mappings['h'] = MOVE_CURSOR_LEFT;
   mappings['l'] = MOVE_CURSOR_RIGHT;

   mappings['8'] = MOVE_CAMERA_UP;
   mappings['2'] = MOVE_CAMERA_DOWN;
   mappings['4'] = MOVE_CAMERA_LEFT;
   mappings['6'] = MOVE_CAMERA_RIGHT;

   mappings['s'] = SAVE_SCORE;
   mappings['w'] = LOAD_SCORE;

   events[SET_TEXT] = []{
      find_text("text").set_text("Hello world!");
   };
   events[CREATE_NOTE_AT_CURSOR] = []{
      find_text("text").set_text("create note at cursor!");
   };
   events[REMOVE_NOTE_AT_CURSOR] = []{
      find_text("text").set_text("remove note at cursor");
   };
   events[CREATE_STAFF_AT_CURSOR] = []{
      find_text("text").set_text("create_staff_at_cursor");
   };
   events[REMOVE_STAFF_AT_CURSOR] = []{
      find_text("text").set_text("remove_staff_at_cursor");
   };
   events[MOVE_CURSOR_UP] = []{
      find_text("text").set_text("move_cursor_up");
   };
   events[MOVE_CURSOR_DOWN] = []{
      find_text("text").set_text("move cursor down");
   };
   events[MOVE_CURSOR_LEFT] = []{
      find_text("text").set_text("move cursor left");
   };
   events[MOVE_CURSOR_RIGHT] = []{
      find_text("text").set_text("move cursor right");
   };
   events[MOVE_CAMERA_UP] = []{
      find_text("text").set_text("move camera up");
   };
   events[MOVE_CAMERA_DOWN] = []{
      find_text("text").set_text("move camera down");
   };
   events[MOVE_CAMERA_LEFT] = []{
      find_text("text").set_text("move camera left");
   };
   events[MOVE_CAMERA_RIGHT] = []{
      find_text("text").set_text("move camera right");
   };
   events[SAVE_SCORE] = []{
      find_text("text").set_text("save score!");
   };
   events[LOAD_SCORE] = []{
      find_text("text").set_text("load score!");
   };
}
