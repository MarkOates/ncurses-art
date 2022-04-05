#pragma once


#include <Quizes/MultiplexQuestion.hpp>
#include <vector>


namespace Quizes
{
   class MultiplexQuestionCollectionHelper
   {
   private:
      std::vector<Quizes::MultiplexQuestion> questions;

   public:
      MultiplexQuestionCollectionHelper(std::vector<Quizes::MultiplexQuestion> questions={});
      ~MultiplexQuestionCollectionHelper();

      std::vector<Quizes::MultiplexQuestion> select_with_dates();
      std::vector<Quizes::MultiplexQuestion> select_with_relevance();
   };
}



