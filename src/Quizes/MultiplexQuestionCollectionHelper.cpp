

#include <Quizes/MultiplexQuestionCollectionHelper.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/String/Trimmer.hpp>


namespace Quizes
{


MultiplexQuestionCollectionHelper::MultiplexQuestionCollectionHelper(std::vector<Quizes::MultiplexQuestion> questions)
   : questions(questions)
{
}


MultiplexQuestionCollectionHelper::~MultiplexQuestionCollectionHelper()
{
}


std::vector<Quizes::MultiplexQuestion> MultiplexQuestionCollectionHelper::select_with_dates()
{
   std::vector<Quizes::MultiplexQuestion> result;
   for (auto &question : questions)
   {
      if (question.get_date().empty()) continue;
      result.push_back(question);
   }
   return result;
}

std::vector<Quizes::MultiplexQuestion> MultiplexQuestionCollectionHelper::select_with_relevance()
{
   std::vector<Quizes::MultiplexQuestion> result;
   for (auto &question : questions)
   {
      if (question.get_relevance().empty()) continue;
      result.push_back(question);
   }
   return result;
}
} // namespace Quizes


