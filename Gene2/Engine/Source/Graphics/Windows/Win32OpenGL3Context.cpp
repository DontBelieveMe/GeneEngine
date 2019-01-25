// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Windows/Win32OpenGL3Context.hpp>
#include <Gene2/Lib/GLFL.Lib.hpp>

#include <Gene2/Debug/Logging.hpp>

using namespace g2::win32;

Win32OpenGL3Context::Win32OpenGL3Context(void* windowHandle)
	: IOpenGL3Context(windowHandle) {
}

namespace g2 {
	namespace internal {
		static HMODULE s_opengl32dll = LoadLibraryA("opengl32.dll");

		static void* GetProcAddress(const char* path) {
			PROC ptr = wglGetProcAddress((LPCSTR)path);

			if (!ptr) {
				return (void*) ::GetProcAddress(s_opengl32dll, (LPCSTR)path);
			}
			else {
				return (void*)ptr;
			}
		}
	}
}

void Win32OpenGL3Context::Create()
{
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		32,
		16,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	m_hdc = GetDC((HWND)m_windowHandle);

	int choosePf = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, choosePf, &pfd);

	m_context = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_context);

	glfl::set_function_loader(g2::internal::GetProcAddress);
	glfl::load_everything();

	int glMajor, glMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
	glGetIntegerv(GL_MINOR_VERSION, &glMinor);

	G2_TRACE("OpenGL Version: {0}.{1}", glMajor, glMinor);

	const GLubyte *vendorString = glGetString(GL_VENDOR);
	G2_TRACE("OpenGL Vendor: {0}", (const char*)vendorString);

	const GLubyte *rendererString = glGetString(GL_RENDERER);
	G2_TRACE("OpenGL Renderer: {0}", (const char*)rendererString);
}

void Win32OpenGL3Context::SwapBuffers()
{
	::SwapBuffers(m_hdc);
}