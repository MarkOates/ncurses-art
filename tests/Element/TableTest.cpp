#include <gtest/gtest.h>

#include <ncurses_art/Element/Table.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(TableTest, can_be_created)
{
   Table menu;
}

TEST(TableTest, has_the_expected_type)
{
   Table menu;
   EXPECT_EQ("Table", menu.get_type());
}

TEST(TableTest, without_arguments_on_construction_sets_the_expected_values)
{
   Table menu;
   std::vector<std::vector<std::string>> expected_elements = {};
   EXPECT_EQ(0, menu.get_x());
   EXPECT_EQ(0, menu.get_y());
   EXPECT_EQ(expected_elements, menu.get_elements());
}

TEST(TableTest, with_arguments_on_construction_sets_the_expected_values)
{
   std::vector<std::vector<std::string>> elements = { { "a", "b", "c" }, { "d", "e", "f" } };
   Table menu(17.125, 195.0, elements);
   EXPECT_EQ(17.125, menu.get_x());
   EXPECT_EQ(195.0, menu.get_y());
   EXPECT_EQ(elements, menu.get_elements());
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
   Table menu;
   menu.set_x(-10);
   ASSERT_EQ(-10, menu.get_x());
   menu.set_x(999);
   ASSERT_EQ(999, menu.get_x());
}

TEST(TableTest, can_get_and_set_the_y_position)
{
   Table menu(0, 9, {});
   ASSERT_EQ(9, menu.get_y());
   menu.set_y(-10);
   ASSERT_EQ(-10, menu.get_y());
   menu.set_y(999);
   ASSERT_EQ(999, menu.get_y());
}

TEST(TableTest, can_return_the_current_selection)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ("a", menu.current_selection());

   menu.move_cursor_right();
   ASSERT_EQ("b", menu.current_selection());
   menu.move_cursor_right();
   ASSERT_EQ("c", menu.current_selection());

   menu.move_cursor_down();
   ASSERT_EQ("f", menu.current_selection());

   menu.move_cursor_left();
   ASSERT_EQ("e", menu.current_selection());
   menu.move_cursor_left();
   ASSERT_EQ("d", menu.current_selection());
   menu.move_cursor_left();
}

TEST(TableTest, moving_the_cursor_horizontally_beyond_the_edge_wraps_around)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ("a", menu.current_selection());

   menu.move_cursor_left();
   ASSERT_EQ("c", menu.current_selection());
   menu.move_cursor_right();
   ASSERT_EQ("a", menu.current_selection());
}

TEST(TableTest, moving_the_cursor_vertically_beyond_the_edge_wraps_around)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ("a", menu.current_selection());

   menu.move_cursor_up();
   ASSERT_EQ("e", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("a", menu.current_selection());
}

TEST(TableTest, current_selection__when_containing_no_elements_is_empty_string)
{
   Table menu(0, 0, {});

   ASSERT_EQ("", menu.current_selection());
}

TEST(TableTest, set_elements__set_the_elements)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });
   std::vector<std::vector<std::string>> elements = { { "x", "y", "z" }, { "u", "v", "w" } };

   ASSERT_TRUE(menu.set_elements(elements));
   ASSERT_EQ(elements, menu.get_elements());
}

TEST(TableTest, when_setting_the_elements_the_current_selection_becomes_the_first_option)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   menu.move_cursor_down();
   menu.move_cursor_right();
   ASSERT_EQ("e", menu.current_selection());

   ASSERT_TRUE(menu.set_elements({ { "x", "y", "z" }, { "u", "v", "w" } }));
   ASSERT_EQ("x", menu.current_selection());
}

TEST(TableTest, when_setting_the_elements_with_invalid_elements_raises_an_exception)
{
   std::vector<std::vector<std::string>> invalid_elements = { { "a", "b" }, { "c", "e", "f" } };
   std::string expected_error_message = "Table error: Num cols on row 1 (3) is not equal to the num cols in the previous row (2)";
   ASSERT_THROW_WITH_MESSAGE(Table(0, 0, invalid_elements), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__set_an_element_to_a_coordinate_within_the_table)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });
   std::vector<std::vector<std::string>> expected_result_elements = { { "a", "y", "c" }, { "d", "x", "z" } };

   menu.set_element(2, 1, "z");
   menu.set_element(1, 1, "x");
   menu.set_element(1, 0, "y");

   ASSERT_EQ(expected_result_elements, menu.get_elements());
}

TEST(TableTest, set_element__when_x_pos_is_less_than_0_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   std::string expected_error_message = "Table [set_element] error: pos_x cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(-1, 0, "foo"), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__when_y_pos_is_less_than_0_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   std::string expected_error_message = "Table [set_element] error: pos_y cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(0, -1, "foo"), std::runtime_error, expected_error_message);
}

TEST(TableTest, set_element__with_an_x_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::set_element error]: pos_x (value: \"2\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(menu.get_num_cols(), 0, "x"), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::set_element error]: pos_x (value: \"3\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(menu.get_num_cols()+1, 0, "x"), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, set_element__with_an_y_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::set_element error]: pos_y (value: \"3\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(0, menu.get_num_rows(), "x"), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::set_element error]: pos_y (value: \"4\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(menu.set_element(0, menu.get_num_rows()+1, "x"), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, can_get_an_set_the_x_cursor_position)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" } });

   ASSERT_EQ(0, menu.get_cursor_pos_x());

   ASSERT_TRUE(menu.set_cursor_pos_x(2));
   ASSERT_EQ(2, menu.get_cursor_pos_x());

   ASSERT_TRUE(menu.set_cursor_pos_x(1));
   ASSERT_EQ(1, menu.get_cursor_pos_x());
}

TEST(TableTest, can_get_an_set_the_y_cursor_position)
{
   Table menu(0, 0, { { "a", "b", "c" }, { "d", "e", "f" }, { "x", "y", "z" }, { "u", "v", "w" } });

   ASSERT_EQ(0, menu.get_cursor_pos_y());

   ASSERT_TRUE(menu.set_cursor_pos_y(2));
   ASSERT_EQ(2, menu.get_cursor_pos_y());

   ASSERT_TRUE(menu.set_cursor_pos_y(3));
   ASSERT_EQ(3, menu.get_cursor_pos_y());
}

TEST(TableTest, when_setting_the_cursor_pos_x_will_modulo_the_position_if_gt_number_of_elements)
{
   Table menu(0, 0, { { "a", "b", "c" } });

   ASSERT_EQ(0, menu.get_cursor_pos_x());

   ASSERT_TRUE(menu.set_cursor_pos_x(3));
   ASSERT_EQ(0, menu.get_cursor_pos_x());

   ASSERT_TRUE(menu.set_cursor_pos_x(7));
   ASSERT_EQ(1, menu.get_cursor_pos_x());
}

TEST(TableTest, when_setting_the_cursor_pos_y_will_modulo_the_position_if_gt_number_of_elements)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ(0, menu.get_cursor_pos_y());

   ASSERT_TRUE(menu.set_cursor_pos_y(3));
   ASSERT_EQ(0, menu.get_cursor_pos_y());

   ASSERT_TRUE(menu.set_cursor_pos_y(7));
   ASSERT_EQ(1, menu.get_cursor_pos_y());
}

TEST(TableTest, get_elements__returns_a_copy_of_the_elements)
{
   std::vector<std::vector<std::string>> expected_elements = { { "a", "b" }, { "c", "d" }, { "e", "f" } };
   Table menu(0, 0, expected_elements);

   ASSERT_EQ(expected_elements, menu.get_elements());
}

TEST(TableTest, get_element_at__returns_the_element_at_a_given_coordinate)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   ASSERT_EQ("a", menu.get_element_at(0, 0));
   ASSERT_EQ("b", menu.get_element_at(1, 0));
   ASSERT_EQ("d", menu.get_element_at(1, 1));
   ASSERT_EQ("f", menu.get_element_at(1, 2));
}

TEST(TableTest, get_element_at__with_an_x_value_less_than_0_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message = "Table [get_element_at] error: x cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(-1, 0), std::runtime_error, expected_error_message);
}

TEST(TableTest, get_element_at__with_an_y_value_less_than_0_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message = "Table [get_element_at] error: y cannot be less than 0";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(0, -1), std::runtime_error, expected_error_message);
}

TEST(TableTest, get_element_at__with_an_x_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::get_element_at error]: x (value: \"2\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(menu.get_num_cols(), 0), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::get_element_at error]: x (value: \"3\") cannot be greater than or equal the number of cols (value: \"2\")";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(menu.get_num_cols()+1, 0), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, get_element_at__with_an_y_value_greater_than_or_equal_to_the_number_of_columns_raises_an_exception)
{
   Table menu(0, 0, { { "a", "b" }, { "c", "d" }, { "e", "f" } });

   std::string expected_error_message_1 = "[Table::get_element_at error]: y (value: \"3\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(0, menu.get_num_rows()), std::runtime_error, expected_error_message_1);

   std::string expected_error_message_2 = "[Table::get_element_at error]: y (value: \"4\") cannot be greater than or equal the number of rows (value: \"3\")";
   ASSERT_THROW_WITH_MESSAGE(menu.get_element_at(0, menu.get_num_rows()+1), std::runtime_error, expected_error_message_2);
}

TEST(TableTest, can_get_the_number_of_columns)
{
   Table menu(0, 0, {});
   ASSERT_EQ(0, menu.get_num_cols());

   ASSERT_TRUE(menu.set_elements({ { "a", "b", "c" } }));
   ASSERT_EQ(3, menu.get_num_cols());

   ASSERT_TRUE(menu.set_elements({ { "a", "b", "c", "d", "e" } }));
   ASSERT_EQ(5, menu.get_num_cols());
}

TEST(TableTest, can_get_the_number_of_rows)
{
   Table menu(0, 0, {});
   ASSERT_EQ(0, menu.get_num_rows());

   ASSERT_TRUE(menu.set_elements({ { "a", "b", "c" }, { "d", "e", "f" } }));
   ASSERT_EQ(2, menu.get_num_rows());

   ASSERT_TRUE(menu.set_elements({ { "a", "b" }, { "c", "d" }, { "e", "f" }, { "g", "h" }, { "i", "j" } }));
   ASSERT_EQ(5, menu.get_num_rows());
}

TEST(TableTest, when_setting_the_cursor_pos_x_to_a_negative_number_throws_an_exception)
{
   Table menu(0, 0, { { "a", "b", "c" } });

   ASSERT_THROW(menu.set_cursor_pos_x(-1), std::runtime_error);
}

TEST(TableTest, when_setting_the_cursor_pos_y_to_a_negative_number_throws_an_exception)
{
   Table menu(0, 0, { { "a", "b", "c" } });

   ASSERT_THROW(menu.set_cursor_pos_y(-1), std::runtime_error);
}

