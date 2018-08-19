#include "Projekt2.h"

// elements
#define TEXT "text"
#define WCHAR_TEXT "wchar_text"
#define FRAME "frame"

// actions
#define SET_TEXT "set_text"

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_wchar_text(WCHAR_TEXT, 10, 21);
   create_text(TEXT, 10, 20);
   create_frame(FRAME, 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   //wchar_t wstr[] = { 189, 9474, L'\0' };

   unsigned c = 9471; // 9471
   int increment = 80;
   std::stringstream name;

   for (int row=2; row<45; row++)
   {
      name << 'a';
      std::wstring wstr;
      for (unsigned i=c; i<c+increment; i++)
      {
         wstr.push_back(i);
         wstr.push_back(L' ');
      }
      row += 1;
      c += increment;
      create_wchar_text(name.str(), 10, row);
      find_wchar_text(name.str()).set_text(wstr);
      //find_wchar_text(name.str()).set_text(L"Hello wchar world!\nYay for you");
   }
}
