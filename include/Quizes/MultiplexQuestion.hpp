#pragma once


#include <string>


namespace Quizes
{
   class MultiplexQuestion
   {
   private:
      std::string date;
      std::string subject;
      std::string subject_type;
      std::string relevance;
      std::string reference_page;

   public:
      MultiplexQuestion(std::string date="[undefined-date]", std::string subject="[undefined-subject]", std::string subject_type="[undefined-subject-type]", std::string relevance="[undefined-subject]", std::string reference_page="[page-not-set]");
      ~MultiplexQuestion();

      void set_date(std::string date);
      void set_subject(std::string subject);
      void set_subject_type(std::string subject_type);
      void set_relevance(std::string relevance);
      void set_reference_page(std::string reference_page);
      std::string get_date();
      std::string get_subject();
      std::string get_subject_type();
      std::string get_relevance();
      std::string get_reference_page();
   };
}



