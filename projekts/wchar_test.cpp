#include <ncurses.h>
#include <locale.h>
#include <wchar.h>

// brew install ncurses

// libraries located at:
//NCURSES_INCLUDE_DIR=/usr/local/opt/ncurses/include
//NCURSES_LIB_DIR=/usr/local/opt/ncurses/lib

// ncurses lib:
//NCURSES_LIB=ncurses

// link with:
//-I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -D_XOPEN_SOURCE_EXTENDED

int main() {  
    setlocale(LC_ALL, "");
    initscr();
    wchar_t wstr[] = { 189, 9474, L'\0' };
    curs_set(0);
    mvaddwstr(10, 10, wstr);
    refresh();
    getch();
    endwin();
    return 0;
}
