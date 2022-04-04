#pragma once


#include <Quizes/MultiplexQuestion.hpp>
#include <vector>


namespace Quizes
{
   class MultiplexQuestionCollectionHelper
   {
   private:
      static std::vector<Quizes::MultiplexQuestion> questions_DUMMY;
      std::vector<Quizes::MultiplexQuestion>& questions;

   public:
      MultiplexQuestionCollectionHelper();
      ~MultiplexQuestionCollectionHelper();

      static std::vector<Quizes::MultiplexQuestion> &get_questions_DUMMY_ref();
      std::vector<Quizes::MultiplexQuestion> select_with_dates();
   };
}



