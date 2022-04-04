

#include <Quizes/MultiplexQuestion.hpp>



namespace Quizes
{


MultiplexQuestion::MultiplexQuestion()
   : date("[undefined-date]")
   , subject("[undefined-subject]")
   , subject_type("[undefined-subject-type]")
   , relevance("[undefined-subject]")
   , reference_page(0)
{
}


MultiplexQuestion::~MultiplexQuestion()
{
}


void MultiplexQuestion::set_date(std::string date)
{
   this->date = date;
}


void MultiplexQuestion::set_subject(std::string subject)
{
   this->subject = subject;
}


void MultiplexQuestion::set_subject_type(std::string subject_type)
{
   this->subject_type = subject_type;
}


void MultiplexQuestion::set_relevance(std::string relevance)
{
   this->relevance = relevance;
}


void MultiplexQuestion::set_reference_page(int reference_page)
{
   this->reference_page = reference_page;
}


std::string MultiplexQuestion::get_date()
{
   return date;
}


std::string MultiplexQuestion::get_subject()
{
   return subject;
}


std::string MultiplexQuestion::get_subject_type()
{
   return subject_type;
}


std::string MultiplexQuestion::get_relevance()
{
   return relevance;
}


int MultiplexQuestion::get_reference_page()
{
   return reference_page;
}


} // namespace Quizes


