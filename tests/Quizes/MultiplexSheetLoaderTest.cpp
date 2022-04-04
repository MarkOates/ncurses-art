
#include <gtest/gtest.h>

#include <Quizes/MultiplexSheetLoader.hpp>


#include <Blast/FileExistenceChecker.hpp>
#define QUIZ_FILE "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Sheet2.csv"


TEST(Quizes_MultiplexSheetLoaderTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexSheetLoader loader;
}


TEST(Quizes_MultiplexSheetLoaderTest, load__loads_the_sheet)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(QUIZ_FILE).exists());

   //std::string quiz_csv = Blast::
   //Quizes::MultiplexSheetLoader loader(
   //loader.load();
}


