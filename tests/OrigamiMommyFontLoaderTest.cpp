
#include <gtest/gtest.h>

#include <OrigamiMommyFontLoader.hpp>


#include <map>
#include <vector>
#include <string>


TEST(OrigamiMommyFontLoaderTest, load__returns_a_map_expecting_certain_values)
{
   OrigamiMommyFontLoader object;
   std::map<char, std::vector<std::string>> letters = object.load();

   char expected_character_key = 'a';
   std::vector<std::string> expected_letter_contents = {
      { "░░░░░" },
      { "█▀▀█ " },
      { "█▄▄█ " },
      { "▀ ░▀ " },
      { "░░░░░" },
   };

   bool letter_exists = (letters.find(expected_character_key) != letters.end());
   EXPECT_EQ(true, letter_exists);
   EXPECT_EQ(expected_letter_contents, letters[expected_character_key]);
}

