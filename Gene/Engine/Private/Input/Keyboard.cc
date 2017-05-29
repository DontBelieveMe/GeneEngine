#include <Input/Keyboard.h>

using namespace Gene::Input;

Gene::Platform::Window * Keyboard::s_PrimaryWindow = nullptr;

void Keyboard::SetPrimaryWindow(Gene::Platform::Window *window)
{
	Keyboard::s_PrimaryWindow = window;
}
