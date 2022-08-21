
#include <gtest/gtest.h>

#include <Quizes/MultiplexSheetLoader.hpp>


#include <Blast/FileExistenceChecker.hpp>
#define QUIZ_FILE "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Capitals.tsv"



#include <string>
#include <fstream>
#include <streambuf>

std::string get_file_contents(std::string filename)
{
   std::ifstream t(filename);
   std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   return str;
}



TEST(Quizes_MultiplexSheetLoaderTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexSheetLoader loader;
}


TEST(Quizes_MultiplexSheetLoaderTest, load__loads_the_sheet)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(QUIZ_FILE).exists());

   std::string file_contents = get_file_contents(QUIZ_FILE);
   Quizes::MultiplexSheetLoader loader(file_contents);
   ASSERT_EQ(true, loader.load());
   ASSERT_EQ(26, loader.get_questions().size());
}


