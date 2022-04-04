

#include <Quizes/MultiplexSheetLoader.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <stdexcept>
#include <sstream>


namespace Quizes
{


MultiplexSheetLoader::MultiplexSheetLoader(std::string raw_csv)
   : raw_csv(raw_csv)
   , questions()
   , loaded(false)
{
}


MultiplexSheetLoader::~MultiplexSheetLoader()
{
}


std::string MultiplexSheetLoader::get_raw_csv()
{
   return raw_csv;
}


bool MultiplexSheetLoader::get_loaded()
{
   return loaded;
}


std::vector<Quizes::MultiplexQuestion> MultiplexSheetLoader::get_questions()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "MultiplexSheetLoader" << "::" << "get_questions" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return questions;
}

void MultiplexSheetLoader::load()
{
   if (!((!loaded)))
      {
         std::stringstream error_message;
         error_message << "MultiplexSheetLoader" << "::" << "load" << ": error: " << "guard \"(!loaded)\" not met";
         throw std::runtime_error(error_message.str());
      }
   const int EXPECTED_NUM_COLUMNS = 6;
   std::vector<std::string> lines = Blast::StringSplitter(raw_csv, '\n').split();
   int line_num = 1;
   for (auto &line : lines)
   {
      std::vector<std::string> columns = Blast::StringSplitter(line, ',').split();
      if (columns.size() != EXPECTED_NUM_COLUMNS)
      {
         std::stringstream error_message;
         error_message << "There was not the expected number of columns ("
                       << EXPECTED_NUM_COLUMNS
                       << ") on line "
                       << line_num << ". Instead, there were "
                       << columns.size() << " columns.";
         throw std::runtime_error(error_message.str());
      }
      
      std::string date = columns[0];
      std::string subject_event_or_document = columns[1];
      std::string subject_person_name_or_symbol = columns[2];
      std::string subject_group = columns[3];
      std::string relevance = columns[4];
      std::string reference_page = columns[5];

      std::string subject_type = "[unextracted-subject-type]";

      

      line_num++;
   }
   loaded = true;
   return;
}

std::string MultiplexSheetLoader::extract_subject_text(std::string event_or_document, std::string person_name_or_symbol, std::string subject_group, int line_number)
{
   //if (event_or_document.empty() && person_name_or_symbol.empty() && subject_group.empty())
   //{
      //std::runtime_error("all 3 cannot be empty");
   //{}
   return "not-extracted";
}
} // namespace Quizes


