

#include <Quizes/MultiplexSheetLoader.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/String/Trimmer.hpp>
#include <Blast/StringSplitter.hpp>
#include <Quizes/MultiplexQuestion.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/String/Trimmer.hpp>


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

bool MultiplexSheetLoader::load()
{
   if (!((!loaded)))
      {
         std::stringstream error_message;
         error_message << "MultiplexSheetLoader" << "::" << "load" << ": error: " << "guard \"(!loaded)\" not met";
         throw std::runtime_error(error_message.str());
      }
   const int EXPECTED_NUM_COLUMNS = 6;
   std::vector<std::string> lines = Blast::StringSplitter(raw_csv, '\n').split();
   bool discard_first_line = true;
   int line_num = 0;

   if (discard_first_line)
   {
      assert(!lines.empty());
      lines.front() = std::move(lines.back());
      lines.pop_back();
      line_num++;
   }

   for (auto &line : lines)
   {
      std::vector<std::string> columns = Blast::StringSplitter(line, '\t').split();
      if (columns.size() != EXPECTED_NUM_COLUMNS)
      {
         std::stringstream error_message;
         error_message << "There was not the expected number of columns ("
                       << EXPECTED_NUM_COLUMNS
                       << ") on line "
                       << line_num << ". Instead, there were "
                       << columns.size() << " columns. "
                       << "The line is \"" << line << "\"";
         throw std::runtime_error(error_message.str());
      }
      
      // name the columns
      std::string date = trim(columns[0]);
      std::string subject_event_or_document = trim(columns[1]);
      std::string subject_person_name_or_symbol = trim(columns[2]);
      std::string subject_group = trim(columns[3]);
      std::string relevance = trim(columns[4]);
      std::string reference_page = trim(columns[5]);

      // swizzle the subject columns
      std::string subject = extract_subject(
         subject_event_or_document, subject_person_name_or_symbol, subject_group, line_num);
      std::string subject_type = extract_subject_type(
         subject_event_or_document, subject_person_name_or_symbol, subject_group);

      // create teh quiz object
      Quizes::MultiplexQuestion question(date, subject, subject_type, relevance, reference_page);

      // add the question to the questions
      questions.push_back(question);

      line_num++;
   }
   loaded = true;
   return true;
}

std::string MultiplexSheetLoader::trim(std::string str)
{
   return Blast::String::Trimmer(str).trim();
}

std::string MultiplexSheetLoader::extract_subject(std::string event_or_document, std::string person_name_or_symbol, std::string subject_group, int line_number)
{
   std::vector<std::string> inputs = { event_or_document, person_name_or_symbol, subject_group };
   for (int i=0; i<inputs.size(); i++)
   {
      if (inputs[i].empty())
      {
         inputs.erase(inputs.begin() + i);
         i--;
      }
   }
   if (inputs.size() != 1)
   {
      std::stringstream error_message;
      error_message << "Only one subject can be present, but none or several was present on line "
                    << line_number << ".";
      throw std::runtime_error(error_message.str());
   }
   return inputs[0];
}

std::string MultiplexSheetLoader::extract_subject_type(std::string event_or_document, std::string person_name_or_symbol, std::string subject_group)
{
   if (!event_or_document.empty()) return "event_or_document";
   if (!person_name_or_symbol.empty()) return "person_name_or_symbol";
   if (!subject_group.empty()) return "subject_group";
   throw std::runtime_error("unexpected extraction of extract_subject_type not valid for some reason.");
   return "[error-path]";
}
} // namespace Quizes


