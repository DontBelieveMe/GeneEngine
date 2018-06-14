// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>
#ifdef GENE_OS_WINDOWS

#include "Win32Window.h" 

#include <Windows.h>
#include <iostream>

#include <Platform/OpenGL.h>
#include <Math/Vector2.h>
#include <Input/Mouse.h>
#include <Input/Keyboard.h>
#include <Input/InputController.h>

#include <Debug/Logger.h>

#define GENE_EVENT_CALLBACK_ID "_GeneCallbacksId"
#define GENE_KEYBOARD_PROP "_GeneKeyboardStateId"
#define GENE_MOUSE_PROP "_GeneMouseProp"

#define GENE_WINDOW_CLASS_NAME "_GeneMainWindow"

using namespace gene::platform::win32;
using namespace gene;

static HDC s_HDC;

static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	using namespace gene::input;
 
    typedef MouseDevice::Button Button;
	gene::platform::EventCallbacks *callbacks = static_cast<gene::platform::EventCallbacks*>(GetProp(hWnd, GENE_EVENT_CALLBACK_ID));
	InputController *inputController = static_cast<InputController*>(GetProp(hWnd, GENE_KEYBOARD_PROP));
    if (!inputController) {
        goto end;
    }
    //MouseButton *mouseButtonState = static_cast<MouseButton*>(GetProp(hWnd, GENE_MOUSE_PROP));
    
    KeyDevice *keyDevice = inputController->GetKeyDevice();
    MouseDevice *mouseDevice = inputController->GetMouseDevice();
    
    Button buttonState = mouseDevice->GetRawButtonState();
    

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		if (callbacks)
		{
			if (callbacks->Resize)
				callbacks->Resize(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_KEYDOWN:
        keyDevice->PressKeyDown(static_cast<Keys>(wParam));
		return 0;
	case WM_KEYUP:
        keyDevice->ReleaseKeyDown(static_cast<Keys>(wParam));
		return 0;
    case WM_LBUTTONDOWN:
        mouseDevice->TrySetButtonState((Button) (static_cast<unsigned>(buttonState) | static_cast<unsigned>(Button::Left)));
        break;
    case WM_LBUTTONUP:
        mouseDevice->TrySetButtonState((Button)(static_cast<unsigned>(buttonState) & ~(static_cast<unsigned>(Button::Left))));
        break;
    case WM_RBUTTONDOWN:
        mouseDevice->TrySetButtonState((Button)(static_cast<unsigned>(buttonState) | static_cast<unsigned>(Button::Right)));
        break;
    case WM_RBUTTONUP:
        mouseDevice->TrySetButtonState((Button)(static_cast<unsigned>(buttonState) & ~(static_cast<unsigned>(Button::Right))));
        break;

	default: break;
	}

    end:
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Win32Window::~Win32Window()
{
}

void Win32Window::Destroy()
{
}

void Win32Window::Create() 
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX _class = { 0 };
	
	_class.cbClsExtra    = 0;
	_class.cbSize        = sizeof(WNDCLASSEX);
	_class.cbWndExtra    = 0;
    _class.hbrBackground = NULL;//(HBRUSH)COLOR_WINDOW;
	_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
	_class.hIcon         = nullptr;
	_class.hIconSm       = nullptr;
	_class.hInstance     = hInstance;
	_class.lpfnWndProc   = (WNDPROC)WinProc;
	_class.lpszClassName = GENE_WINDOW_CLASS_NAME;
	_class.lpszMenuName  = nullptr;
	_class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// TODO: Error handling
	RegisterClassEx(&_class);
	
	// TODO: This has removed Win32 borderless functionality, reimplement this
	DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

    RECT rect;
    rect.left = rect.top = 0;
    rect.right = Width();
    rect.bottom = Height();
    AdjustWindowRect(&rect, style, false);
	

	m_Handle = CreateWindowEx(
		0,
		GENE_WINDOW_CLASS_NAME,	
		m_WindowConfig.Title,
		style,
		200, 200,
		rect.right - rect.left, rect.bottom - rect.top,
		nullptr,
		nullptr,
		hInstance, nullptr
	);

    SetProp((HWND)m_Handle, GENE_KEYBOARD_PROP, &m_InputController);

	SetProp((HWND)m_Handle, GENE_EVENT_CALLBACK_ID, &m_Callbacks);
    SetProp((HWND)m_Handle, GENE_MOUSE_PROP, &(m_MouseState.m_Button));
	input::Mouse::SetPrimaryWindow(this);
	input::Keyboard::SetPrimaryWindow(this);

	memset(m_KeyState.KeyMap, 0, 62256);

    m_MouseState.m_Button = gene::input::MouseButton::None;

	CreateGLContext();
}

static HMODULE s_OpenGL32 = LoadLibraryA("opengl32.dll");

static void *Win32GetProcAddress(const char* path)
{
	PROC ptr = wglGetProcAddress((LPCSTR)path);
	if (ptr == NULL)
		return (void*)::GetProcAddress(s_OpenGL32, (LPCSTR)path);
	else
		return (void*)ptr;
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
		0, 0,
		0, 0, 0, 0, 0,
		32,                       
		16,                
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

    const GLubyte *versionString = glGetString(GL_VERSION);
    LOG(LogLevel::Infomation, "OpenGL Version: ", versionString);
    
    glViewport(0, 0, Width(), Height());
}

void Win32Window::Show()
{
    if (m_WindowConfig.Borderless)
    {
        SetWindowLongPtr((HWND)m_Handle, GWL_STYLE,
            WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
    }

	ShowWindow((HWND)m_Handle, SW_SHOW);
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
            Vector2i pos;
            pos.X = cursorPos.x;
            pos.Y = cursorPos.y;

            m_InputController.GetMouseDevice()->TrySetCursorPosition(pos);
            /*m_MouseState.m_Position.X = cursorPos.x;//static_cast<float>(cursorPos.x);
            m_MouseState.m_Position.Y = cursorPos.y;//static_cast<float>(cursorPos.y);*/
		}
	}
}

void Win32Window::SwapBuffers()
{
	::SwapBuffers(s_HDC);
}

Vector2 Win32Window::ScreenToWindow(const Vector2& point)
{
	RECT winRect;
	GetWindowRect((HWND)m_Handle, &winRect);
	Vector2 screenPos(point.X - winRect.left, point.Y - winRect.top);
	return screenPos;
}

Vector2 Win32Window::WindowToScreen(const Vector2& point)
{
	RECT winRect;
	GetWindowRect((HWND)m_Handle, &winRect);
	Vector2 screenPos(point.X + winRect.left, point.Y + winRect.top);
	return screenPos;
}

#endif
