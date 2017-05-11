#include <Platform/Window.h>
#include <Platform/OS.h>
#include <Platform/OpenGL.h>
#include <Graphics/Color.h>

using namespace Gene::Platform;
using namespace Gene::Graphics;

Window::Window(WindowInfo info):
	m_WindowConfig(info)
{
	m_Context = new GLContext();
}

void Window::SetClearColor(Color color)
{
	glClearColor(
		color.LinearR(), color.LinearG(), color.LinearB(), color.LinearA());
}

#if defined(GENE_OS_WINDOWS)
	#include "Win32/Win32Window.h"
	Window *Window::CreateWindow(WindowInfo info) { return new Gene::Platform::Win32::Win32Window(info);  }
#elif defined(GENE_OS_LINUX)
    #include "Linux/X11Window.h"
    Window *Window::CreateWindow(WindowInfo info) { return new Gene::Platform::X11::X11Window(info); }
#else
	#error [[GENE Engine Compile Error]]: Unknown Platform/OS! - (Cannot Create Window)
#endif
