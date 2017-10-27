#include <Platform/Window.h>
#include <Platform/OS.h>
#include <Platform/OpenGL.h>
#include <Graphics/Color.h>

#if defined(GENE_OS_WINDOWS)
	#include "Win32/Win32Window.h"
	using PlatformWindow = Gene::Platform::Win32::Win32Window;
#elif defined(GENE_OS_LINUX)
    #include "Linux/X11Window.h"
	using PlatformWindow = Gene::Platform::X11::X11Window;
#else
	#error [[GENE Engine Compile Error]]: Unknown Platform/OS! - (Cannot Create Window)
#endif

using namespace Gene::Platform;
using namespace Gene::Graphics;

Window::Window(WindowInfo info):
	m_WindowConfig(info)
{
	m_Context = new GLContext();
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SetClearColor(Color color)
{
	glClearColor(
		color.LinearR(), color.LinearG(), color.LinearB(), color.LinearA());
}

Window *Window::CreateWindow(WindowInfo info) 
{
	return new PlatformWindow(info);
}
