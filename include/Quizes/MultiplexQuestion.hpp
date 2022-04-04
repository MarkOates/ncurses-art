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
      int reference_page;

   public:
      MultiplexQuestion();
      ~MultiplexQuestion();

      void set_date(std::string date);
      void set_subject(std::string subject);
      void set_subject_type(std::string subject_type);
      void set_relevance(std::string relevance);
      void set_reference_page(int reference_page);
      std::string get_date();
      std::string get_subject();
      std::string get_subject_type();
      std::string get_relevance();
      int get_reference_page();
   };
}



