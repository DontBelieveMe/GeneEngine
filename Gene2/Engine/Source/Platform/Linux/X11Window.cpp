#include <Gene2/Platform/Linux/X11Window.hpp>

using namespace g2;
using namespace g2::x11;

void X11Window::Close() {}

X11Window::X11Window(const WindowConfig& config)
	: IWindow(config) {}

void X11Window::Init() {}

void X11Window::Show() {}

void X11Window::ProcessPlatformEvents() {}
