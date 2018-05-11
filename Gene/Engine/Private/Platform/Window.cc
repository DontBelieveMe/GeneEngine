// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/Window.h>
#include <Platform/OS.h>
#include <Platform/OpenGL.h>
#include <Graphics/Color.h>
#include <Debug/Logger.h>

#define S_IMP(x) #x
#define STRINGIFY_PLATFORM(platform) \
    S_IMP(platform)

#if defined(GENE_OS_WINDOWS)
#include <Windows.h>
#undef CreateWindow
	#include "Win32/Win32Window.h"
	using PlatformWindow = Gene::Platform::Win32::Win32Window;
#define OS Windows
#elif defined(GENE_OS_LINUX)
    #include "Linux/X11Window.h"
	using PlatformWindow = Gene::Platform::X11::X11Window;
#define OS Linux
#elif defined(GENE_OS_ANDROID)
	#include "Android/AWindow.h"
	using PlatformWindow = Gene::Platform::Android::AWindow;
#define OS Android
#else
	#error [[GENE Engine Compile Error]]: Unknown Platform/OS!
#endif

using namespace Gene::Platform;
using namespace Gene::Graphics;
using namespace Gene;

void PrintSystemInfo()
{
    LOG(LogLevel::Infomation, "------- ---------------------- -------");
    LOG(LogLevel::Infomation, "------- Starting Debug Session -------");
    LOG(LogLevel::Infomation, "------- ---------------------- -------");

    LOG(LogLevel::Infomation, "Operating System: ", STRINGIFY_PLATFORM(OS));
}

#if defined(GENE_OS_ANDROID)
	#include "../../../ThirdParty/android/android_native_app_glue.h"

	void android_main(struct android_app* state)
	{
        PrintSystemInfo();
        PlatformWindow::s_AndroidAppState = state;
		GeneMain(0, nullptr);
	}
#else
	int main(int argc, char **argv)
	{
        PrintSystemInfo();
		GeneMain(argc, argv);
	}
#endif

Window::Window(WindowInfo info):
	m_WindowConfig(info)
{
	m_Context = new GLContext();
}

void Window::Clear() 
{
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
