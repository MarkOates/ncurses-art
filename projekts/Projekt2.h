#include <Projekt.h>

#include <ncurses.h>

#include <map>

#include "projekt_helper.h"

Projekt::Projekt() { current_project = this; }

std::map<char, std::string> mappings = {
   { 'q', EVENT_ABORT_PROGRAM },
};

void initialize();

std::map<std::string, void(*)()> events = {
   { EVENT_PROGRAM_INITIALIZED, initialize },
};

bool Projekt::process_input(char input_ch)
{
   if (mappings.find(input_ch) == mappings.end()) return false;
   return emit_event(mappings[input_ch]);
}

bool Projekt::process_event(std::string e)
{
   if (events.find(e) == events.end()) return false;
   events[e]();
   return true;
}
