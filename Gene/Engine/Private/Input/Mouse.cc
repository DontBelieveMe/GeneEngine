#include <Input/Mouse.h>
#include <Platform/OS.h>

using namespace Gene::Input;

Gene::Platform::Window *Mouse::s_PrimaryWindow = nullptr;

void Mouse::SetPrimaryWindow(Gene::Platform::Window *window)
{
	Mouse::s_PrimaryWindow = window;
}