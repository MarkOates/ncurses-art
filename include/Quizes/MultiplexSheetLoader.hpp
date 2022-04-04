#pragma once


#include <Quizes/MultiplexQuestion.hpp>
#include <string>
#include <vector>


namespace Quizes
{
   class MultiplexSheetLoader
   {
   private:
      std::string raw_csv;
      std::vector<Quizes::MultiplexQuestion> questions;
      bool loaded;

   public:
      MultiplexSheetLoader(std::string raw_csv="");
      ~MultiplexSheetLoader();

      std::string get_raw_csv();
      bool get_loaded();
      std::vector<Quizes::MultiplexQuestion> get_questions();
      bool load();
      std::string trim(std::string str="");
      std::string extract_subject(std::string event_or_document="[not-set]", std::string person_name_or_symbol="[not-set]", std::string subject_group="[not-set]", int line_number=0);
      std::string extract_subject_type(std::string event_or_document="[not-set]", std::string person_name_or_symbol="[not-set]", std::string subject_group="[not-set]");
   };
}



