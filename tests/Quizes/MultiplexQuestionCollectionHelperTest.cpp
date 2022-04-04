
#include <gtest/gtest.h>

#include <Quizes/MultiplexQuestionCollectionHelper.hpp>


TEST(Quizes_MultiplexQuestionCollectionHelperTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexQuestionCollectionHelper multiplex_question_collection_helper;
}


TEST(Quizes_MultiplexQuestionCollectionHelperTest, run__returns_the_expected_response)
{
   Quizes::MultiplexQuestionCollectionHelper multiplex_question_collection_helper;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, multiplex_question_collection_helper.run());
}

