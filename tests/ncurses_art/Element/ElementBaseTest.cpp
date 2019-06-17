#include <gtest/gtest.h>

#include <ncurses_art/Element/ElementBase.hpp>

class DerivedElement : public ElementBase
{
public:
   DerivedElement() : ElementBase("DerivedElement") {}
   void draw() override {}
};

TEST(ElementBaseTest, derived_classes_can_be_created)
{
   DerivedElement derived_element;
}

TEST (ElementBaseTest, initializes_with_a_default_name_of_empty_string)
{
   DerivedElement derived_element;
   ASSERT_EQ("", derived_element.get_name());
}

TEST (ElementBaseTest, can_set_and_get_the_name)
{
   DerivedElement derived_element;

   ASSERT_TRUE(derived_element.set_name("foo"));
   ASSERT_EQ("foo", derived_element.get_name());

   ASSERT_TRUE(derived_element.set_name("bar"));
   ASSERT_EQ("bar", derived_element.get_name());

   ASSERT_TRUE(derived_element.set_name("baz"));
   ASSERT_EQ("baz", derived_element.get_name());
}

TEST (ElementBaseTest, can_get_the_type)
{
   DerivedElement derived_element;
   ASSERT_EQ("DerivedElement", derived_element.get_type());
}

TEST (ElementBaseTest, returns_true_if_type_matches)
{
   DerivedElement derived_element;
   ASSERT_TRUE(derived_element.is_type("DerivedElement"));
}

TEST (ElementBaseTest, returns_false_if_type_matches)
{
   DerivedElement derived_element;
   ASSERT_FALSE(derived_element.is_type("NotTheCorrectElementName"));
}

TEST (ElementBaseTest, returns_true_if_name_matches)
{
   DerivedElement derived_element;
   ASSERT_TRUE(derived_element.set_name("foo"));
   ASSERT_TRUE(derived_element.is_name("foo"));
}

TEST (ElementBaseTest, returns_false_if_name_matches)
{
   DerivedElement derived_element;
   ASSERT_TRUE(derived_element.set_name("foo"));
   ASSERT_FALSE(derived_element.is_name("baz"));
}
