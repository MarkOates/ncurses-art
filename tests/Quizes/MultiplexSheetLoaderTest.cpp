
#include <gtest/gtest.h>

#include <Quizes/MultiplexSheetLoader.hpp>


TEST(Quizes_MultiplexSheetLoaderTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexSheetLoader loader;
}


TEST(Quizes_MultiplexSheetLoaderTest, load__loads_the_sheet)
{
   Quizes::MultiplexSheetLoader loader;
   loader.load();
}


