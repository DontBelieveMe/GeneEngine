#include <Graphics/GUI/TextBox.h>
#include <Input/Keyboard.h>
#include <Input/Keys.h>

using namespace Gene::Graphics::GUI;
using namespace Gene::Graphics;

TextBox::TextBox(Font *font): TextFont(font)
{
}

void TextBox::Draw(Renderer2D *renderer) 
{
    renderer->DrawString(TextFont, Text, Position, Color::Black);
}

void TextBox::KeyDown(Gene::Input::Keys key)
{
    Text += Input::Keyboard::KeyToASCII(key);
}