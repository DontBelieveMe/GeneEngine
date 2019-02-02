// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Windows/Win32OpenGL3Context.hpp>
#include <Gene2/Lib/GLFL.Lib.hpp>

#include <Gene2/Debug/Assert.hpp>
#include <Gene2/Debug/Logging.hpp>

using namespace g2::win32;

Win32OpenGL3Context::Win32OpenGL3Context(void* windowHandle, g2::ContextAttributes attribs)
	: IOpenGL3Context(windowHandle, attribs) {
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

	// We need to create a legacy context first in order to use wglCreateContextAttribsARB
	HGLRC legacyContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, legacyContext);
	
	typedef HGLRC(_stdcall *WGL_CreateContextAttribsARB)(HDC, HDC, const int*);
	WGL_CreateContextAttribsARB wglCreateContextAttribsARB = (WGL_CreateContextAttribsARB) wglGetProcAddress("wglCreateContextAttribsARB");

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
	
	// Default to the compatibility profile if the Profile attribute is invalid
	int profile = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

	switch (m_attributes.Profile)
	{
	case AG_PROFILE_CORE:
		profile = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
		break;
	case AG_PROFILE_COMPATIBILITY:
		profile = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
		break;
	}

	// Attributes is an array of <name, value> pairs, terminated with a 0.
	int contextAttributes[] = 
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, m_attributes.TargetMajorVersion,
		WGL_CONTEXT_MINOR_VERSION_ARB, m_attributes.TargetMinorVersion,
		WGL_CONTEXT_PROFILE_MASK_ARB, profile,
		0
	};

	m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttributes);
	
	// Delete the temporary legacy context we no longer use
	wglDeleteContext(legacyContext);

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