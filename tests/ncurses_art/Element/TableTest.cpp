#include <gtest/gtest.h>

#include <ncurses_art/Element/Table.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(TableTest, can_be_created)
{
   Table table;
}

TEST(TableTest, has_the_expected_type)
{
   Table table;
   EXPECT_EQ("Table", table.get_type());
}

TEST(TableTest, without_arguments_on_construction_sets_the_expected_values)
{
   Table table;
   std::vector<std::vector<std::string>> expected_elements = {};
   EXPECT_EQ(0, table.get_x());
   EXPECT_EQ(0, table.get_y());
   EXPECT_EQ(expected_elements, table.get_elements());
}

TEST(TableTest, with_arguments_on_construction_sets_the_expected_values)
{
   std::vector<std::vector<std::string>> elements = { { "a", "b", "c" }, { "d", "e", "f" } };
   Table table(17.125, 195.0, elements);
   EXPECT_EQ(17.125, table.get_x());
   EXPECT_EQ(195.0, table.get_y());
   EXPECT_EQ(elements, table.get_elements());
}

TEST(TableTest, when_constructing_with_invalid_elements_raises_an_exception)
{
   Table table(0, 0, {});
   std::vector<std::vector<std::string>> invalid_elements = { { "a", "b", "c" }, { "e", "f" } };
   std::string expected_error_message = "Table error: Num cols on row 1 (2) is not equal to the num cols in the previous row (3)";
   ASSERT_THROW_WITH_MESSAGE(table.set_elements(invalid_elements), std::runtime_error, expected_error_message);
}

TEST(TableTest, can_get_and_set_the_x_position)
{
   Table table;
   table.set_x(-10);
   ASSERT_EQ(-10, table.get_x());
   table.set_x(999);
   ASSERT_EQ(999, table.get_x());
}

TEST(TableTest, can_get_and_set_the_y_position)
{
   Table table(0, 9, {});
   ASSERT_EQ(9, table.get_y());
   table.set_y(-10);
   ASSERT_EQ(-10, table.get_y());
   table.set_y(999);
   ASSERT_EQ(999, table.get_y());
}

TEST(TableTest, can_return_the_current_selection)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ("a", table.current_selection());

   table.move_cursor_right();
   ASSERT_EQ("b", table.current_selection());
   table.move_cursor_right();
   ASSERT_EQ("c", table.current_selection());

   table.move_cursor_down();
   ASSERT_EQ("f", table.current_selection());

   table.move_cursor_left();
   ASSERT_EQ("e", table.current_selection());
   table.move_cursor_left();
   ASSERT_EQ("d", table.current_selection());
   table.move_cursor_left();
}

TEST(TableTest, moving_the_cursor_horizontally_beyond_the_edge_wraps_around)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ("a", table.current_selection());

   table.move_cursor_left();
   ASSERT_EQ("c", table.current_selection());
   table.move_cursor_right();
   ASSERT_EQ("a", table.current_selection());
}

TEST(TableTest, moving_the_cursor_vertically_beyond_the_edge_wraps_around)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ("a", table.current_selection());

   table.move_cursor_up();
   ASSERT_EQ("e", table.current_selection());
   table.move_cursor_down();
   ASSERT_EQ("a", table.current_selection());
}

TEST(TableTest, current_selection__when_containing_no_elements_is_empty_string)
{
   Table table(0, 0, {});

   ASSERT_EQ("", table.current_selection());
}

TEST(TableTest, set_elements__set_the_elements)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });
   std::vector<std::vector<std::string>> elements = { { "x", "y", "z" }, { "u", "v", "w" } };

   ASSERT_TRUE(table.set_elements(elements));
   ASSERT_EQ(elements, table.get_elements());
}

TEST(TableTest, when_setting_the_elements_the_current_selection_becomes_the_first_option)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   table.move_cursor_down();
   table.move_cursor_right();
   ASSERT_EQ("e", table.current_selection());

   ASSERT_TRUE(table.set_elements({ { "x", "y", "z" }, { "u", "v", "w" } }));
   ASSERT_EQ("x", table.current_selection());
}

TEST(TableTest, when_setting_the_elements_with_invalid_elements_raises_an_exception)
{
   std::vector<std::vector<std::string>> invalid_elements = { { "a", "b" }, { "c", "e", "f" } };
   std::string expected_error_message = "Table error: Num cols on row 1 (3) is not equal to the num cols in the previous row (2)";
   ASSERT_THROW_WITH_MESSAGE(Table(0, 0, invalid_elements), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__set_an_element_to_a_coordinate_within_the_table)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });
   std::vector<std::vector<std::string>> expected_result_elements = { { "a", "y", "c" }, { "d", "x", "z" } };

   table.set_element(2, 1, "z");
   table.set_element(1, 1, "x");
   table.set_element(1, 0, "y");

   ASSERT_EQ(expected_result_elements, table.get_elements());
}

TEST(TableTest, set_element__when_x_pos_is_less_than_0_raises_an_exception)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   std::string expected_error_message = "Table [set_element] error: pos_x cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(-1, 0, "foo"), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__when_y_pos_is_less_than_0_raises_an_exception)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   std::string expected_error_message = "Table [set_element] error: pos_y cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(0, -1, "foo"), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__with_an_x_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::set_element error]: pos_x (value: \"2\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(table.get_num_cols(), 0, "x"), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::set_element error]: pos_x (value: \"3\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(table.get_num_cols()+1, 0, "x"), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, set_element__with_an_y_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::set_element error]: pos_y (value: \"3\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(0, table.get_num_rows(), "x"), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::set_element error]: pos_y (value: \"4\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(table.set_element(0, table.get_num_rows()+1, "x"), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, can_get_an_set_the_x_cursor_position)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ(0, table.get_cursor_pos_x());

   ASSERT_TRUE(table.set_cursor_pos_x(2));
   ASSERT_EQ(2, table.get_cursor_pos_x());

   ASSERT_TRUE(table.set_cursor_pos_x(1));
   ASSERT_EQ(1, table.get_cursor_pos_x());
}

TEST(TableTest, can_get_an_set_the_y_cursor_position)
{
   Table table(0, 0, { { "a", "b", "c" }, { "d", "e", "f" }, { "x", "y", "z" }, { "u", "v", "w" } });

   ASSERT_EQ(0, table.get_cursor_pos_y());

   ASSERT_TRUE(table.set_cursor_pos_y(2));
   ASSERT_EQ(2, table.get_cursor_pos_y());

   ASSERT_TRUE(table.set_cursor_pos_y(3));
   ASSERT_EQ(3, table.get_cursor_pos_y());
}

TEST(TableTest, when_setting_the_cursor_pos_x_will_modulo_the_position_if_gt_number_of_elements)
{
   Table table(0, 0, { { "a", "b", "c" } });

   ASSERT_EQ(0, table.get_cursor_pos_x());

   ASSERT_TRUE(table.set_cursor_pos_x(3));
   ASSERT_EQ(0, table.get_cursor_pos_x());

   ASSERT_TRUE(table.set_cursor_pos_x(7));
   ASSERT_EQ(1, table.get_cursor_pos_x());
}

TEST(TableTest, when_setting_the_cursor_pos_y_will_modulo_the_position_if_gt_number_of_elements)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ(0, table.get_cursor_pos_y());

   ASSERT_TRUE(table.set_cursor_pos_y(3));
   ASSERT_EQ(0, table.get_cursor_pos_y());

   ASSERT_TRUE(table.set_cursor_pos_y(7));
   ASSERT_EQ(1, table.get_cursor_pos_y());
}

TEST(TableTest, get_elements__returns_a_copy_of_the_elements)
{
   std::vector<std::vector<std::string>> expected_elements = { { "a", "b" }, { "c", "d" }, { "e", "f" } };
   Table table(0, 0, expected_elements);

   ASSERT_EQ(expected_elements, table.get_elements());
}

TEST(TableTest, get_element_at__returns_the_element_at_a_given_coordinate)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ("a", table.get_element_at(0, 0));
   ASSERT_EQ("b", table.get_element_at(1, 0));
   ASSERT_EQ("d", table.get_element_at(1, 1));
   ASSERT_EQ("f", table.get_element_at(1, 2));
}

TEST(TableTest, get_element_at__with_an_x_value_less_than_0_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message = "Table [get_element_at] error: x cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(-1, 0), std::runtime_error, expected_error_message);
}

TEST(TableTest, get_element_at__with_an_y_value_less_than_0_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message = "Table [get_element_at] error: y cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(0, -1), std::runtime_error, expected_error_message);
}

TEST(TableTest, get_element_at__with_an_x_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::get_element_at error]: x (value: \"2\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(table.get_num_cols(), 0), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::get_element_at error]: x (value: \"3\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(table.get_num_cols()+1, 0), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, get_element_at__with_an_y_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table table(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::get_element_at error]: y (value: \"3\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(0, table.get_num_rows()), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::get_element_at error]: y (value: \"4\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(table.get_element_at(0, table.get_num_rows()+1), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, can_get_the_number_of_columns)
{
   Table table(0, 0, {});
   ASSERT_EQ(0, table.get_num_cols());

   ASSERT_TRUE(table.set_elements({ { "a", "b", "c" } }));
   ASSERT_EQ(3, table.get_num_cols());

   ASSERT_TRUE(table.set_elements({ { "a", "b", "c", "d", "e" } }));
   ASSERT_EQ(5, table.get_num_cols());
}

TEST(TableTest, can_get_the_number_of_rows)
{
   Table table(0, 0, {});
   ASSERT_EQ(0, table.get_num_rows());

   ASSERT_TRUE(table.set_elements({ { "a", "b", "c" }, { "d", "e", "f" } }));
   ASSERT_EQ(2, table.get_num_rows());

   ASSERT_TRUE(table.set_elements({ { "a", "b" }, { "c", "d" }, { "e", "f" }, { "g", "h" }, { "i", "j" } }));
   ASSERT_EQ(5, table.get_num_rows());
}

TEST(TableTest, when_setting_the_cursor_pos_x_to_a_negative_number_throws_an_exception)
{
   Table table(0, 0, { { "a", "b", "c" } });

   ASSERT_THROW(table.set_cursor_pos_x(-1), std::runtime_error);
}

TEST(TableTest, when_setting_the_cursor_pos_y_to_a_negative_number_throws_an_exception)
{
   Table table(0, 0, { { "a", "b", "c" } });

   ASSERT_THROW(table.set_cursor_pos_y(-1), std::runtime_error);
}

