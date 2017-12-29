#include <gtest/gtest.h>

#include <ncurses_art/Element/ElementBase.h>

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
