

#include <Quizes/MultiplexQuestionCollectionHelper.hpp>
#include <Blast/String/Trimmer.hpp>


namespace Quizes
{


std::vector<Quizes::MultiplexQuestion> MultiplexQuestionCollectionHelper::questions_DUMMY = {};


MultiplexQuestionCollectionHelper::MultiplexQuestionCollectionHelper()
   : questions(get_questions_DUMMY_ref())
{
}


MultiplexQuestionCollectionHelper::~MultiplexQuestionCollectionHelper()
{
}


std::vector<Quizes::MultiplexQuestion> &MultiplexQuestionCollectionHelper::get_questions_DUMMY_ref()
{
   return questions_DUMMY;
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
} // namespace Quizes


