#include <ncurses_art/Element/TextInput.hpp>

#include <ncurses_art/Element/Frame.hpp>
#include <ncurses_art/Element/Text.hpp>

TextInput::TextInput(float x, float y, std::string label, float width)
   : ElementBase("TextInput")
   , x(x)
   , y(y)
   , label(label)
   , value("")
   , width(width)
{}

TextInput::~TextInput()
{}

bool TextInput::set_x(float x)
{
   this->x = x;
   return true;
}

bool TextInput::set_y(float y)
{
   this->y = y;
   return true;
}

bool TextInput::set_label(std::string label)
{
   this->label = label;
   return true;
}

bool TextInput::set_value(std::string value)
{
   this->value = value;
   return true;
}

bool TextInput::set_width(float width)
{
   this->width = width;
   return true;
}

float TextInput::get_x()
{
   return x;
}

float TextInput::get_y()
{
   return y;
}

std::string TextInput::get_label()
{
   return label;
}

std::string TextInput::get_value()
{
   return value;
}

float TextInput::get_width()
{
   return width;
}

void TextInput::draw()
{
   Frame frame(x, y, width, 3);
   frame.draw();

   Text label_text(label, x-3, y+1, 1.0);
   label_text.draw();

   Text input_text(value, x+3, y+1);
   input_text.draw();
}
