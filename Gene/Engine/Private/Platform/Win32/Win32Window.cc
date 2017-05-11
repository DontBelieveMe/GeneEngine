#include <Platform/OS.h>
#ifdef GENE_OS_WINDOWS

#include "Win32Window.h" 

#include <Windows.h>
#include <iostream>

#include <Platform/OpenGL.h>
#include <Math/Vector2.h>
#include <Input/Mouse.h>

using namespace Gene::Platform::Win32;

static HDC s_HDC;

static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default: break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Win32Window::~Win32Window()
{
}

void Win32Window::Create() 
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX _class = { 0 };
	
	_class.cbClsExtra = 0;
	_class.cbSize = sizeof(WNDCLASSEX);
	_class.cbWndExtra = 0;
	_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
	_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	_class.hIcon = nullptr;
	_class.hIconSm = nullptr;
	_class.hInstance = hInstance;
	_class.lpfnWndProc = (WNDPROC)WinProc;
	_class.lpszClassName = "_GeneMainWindow";
	_class.lpszMenuName = nullptr;
	_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// TODO: Error handling
	RegisterClassEx(&_class);

	m_Handle = CreateWindowEx(
		0,
		"_GeneMainWindow",
		m_WindowConfig.Title,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		Width(), Height(),
		nullptr,
		nullptr,
		hInstance, nullptr
	);

	Input::Mouse::SetPrimaryWindow(this);
}

static HMODULE s_OpenGL32 = LoadLibraryA("opengl32.dll");

static void *Win32GetProcAddress(const char* path)
{
	void * ptr = wglGetProcAddress((LPCSTR)path);
	if (ptr == NULL)
		return ::GetProcAddress(s_OpenGL32, (LPCSTR)path);
	else
		return ptr;
}

void Win32Window::CreateGLContext()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
		PFD_TYPE_RGBA,
		32,                        
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                       
		8,                
		0,                      
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC hdc = GetDC((HWND)m_Handle);
	s_HDC = hdc;
	int choosePf = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, choosePf, &pfd);

	HGLRC context = wglCreateContext(hdc);
	BOOL s = wglMakeCurrent(hdc, context);

	m_Context->Context = context;

	glfl::set_function_loader(Win32GetProcAddress);
	glfl::load_everything();

	glGetIntegerv(GL_MAJOR_VERSION, &(m_Context->MajorVersion));
	glGetIntegerv(GL_MINOR_VERSION, &(m_Context->MinorVersion));
}

void Win32Window::Show()
{
	ShowWindow((HWND)m_Handle, 1);
}

void Win32Window::PollEvents()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_Running = false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	POINT cursorPos;
	if (GetCursorPos(&cursorPos))
	{
		if (ScreenToClient((HWND)m_Handle, &cursorPos))
		{
			m_MouseState.Position.X = static_cast<float>(cursorPos.x);
			m_MouseState.Position.Y = static_cast<float>(cursorPos.y);
		}
	}

	// auto clear screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void Win32Window::SwapBuffers()
{
	::SwapBuffers(s_HDC);
}
#endif
