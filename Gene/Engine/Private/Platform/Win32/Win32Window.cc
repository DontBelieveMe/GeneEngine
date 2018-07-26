// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>
#ifdef GENE_OS_WINDOWS

#include "Win32Window.h" 

#include <Graphics/ImGui.h>

#include <Windows.h>
#include <iostream>

#include <Platform/OpenGL.h>
#include <Math/Vector2.h>

#include <Input/InputController.h>

#include <Debug/Logger.h>

#define GENE_EVENT_CALLBACK_ID "_GeneCallbacksId"
#define GENE_KEYBOARD_PROP "_GeneKeyboardStateId"
#define GENE_MOUSE_PROP "_GeneMouseProp"

#define GENE_WINDOW_CLASS_NAME "_GeneMainWindow"

using namespace gene::platform::win32;
using namespace gene;

static HDC s_HDC;

static bool ImGui_ImplWin32_UpdateMouseCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return false;

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
    {
        // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
        ::SetCursor(NULL);
    }
    else
    {
        // Show OS mouse cursor
        LPTSTR win32_cursor = IDC_ARROW;
        switch (imgui_cursor)
        {
        case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
        case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
        case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
        case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
        case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
        case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
        case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
        case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
        }
        ::SetCursor(::LoadCursor(NULL, win32_cursor));
    }
    return true;
}

static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	using namespace gene::input;
    

	gene::platform::EventCallbacks *callbacks = static_cast<gene::platform::EventCallbacks*>(GetProp(hWnd, GENE_EVENT_CALLBACK_ID));
   
	InputController *inputController = static_cast<InputController*>(GetProp(hWnd, GENE_KEYBOARD_PROP));
    // TODO: This needs to be handled/fixed
    if (!inputController) {
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
   
    ImGuiIO& io = ImGui::GetIO();
    KeyDevice *keyDevice = inputController->GetKeyDevice();
    MouseDevice *mouseDevice = inputController->GetMouseDevice();
    
    MouseButton buttonState = mouseDevice->GetRawButtonState();

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
        break;
	case WM_KEYUP:
        keyDevice->ReleaseKeyDown(static_cast<Keys>(wParam));
        break;
    case WM_LBUTTONDOWN:
        mouseDevice->TrySetButtonState((MouseButton) (static_cast<unsigned>(buttonState) | static_cast<unsigned>(MouseButton::Left)));
        break;
    case WM_LBUTTONUP:
        mouseDevice->TrySetButtonState((MouseButton)(static_cast<unsigned>(buttonState) & ~(static_cast<unsigned>(MouseButton::Left))));
        break;
    case WM_RBUTTONDOWN:
        mouseDevice->TrySetButtonState((MouseButton)(static_cast<unsigned>(buttonState) | static_cast<unsigned>(MouseButton::Right)));
        break;
    case WM_RBUTTONUP:
        mouseDevice->TrySetButtonState((MouseButton)(static_cast<unsigned>(buttonState) & ~(static_cast<unsigned>(MouseButton::Right))));
        break;

	default: break;
	}

    switch (msg)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
    {
        int button = 0;
        if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
        if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
        if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
        if (!ImGui::IsAnyMouseDown() && ::GetCapture() == NULL)
            ::SetCapture(hWnd);
        io.MouseDown[button] = true;
        return 0;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    {
        int button = 0;
        if (msg == WM_LBUTTONUP) button = 0;
        if (msg == WM_RBUTTONUP) button = 1;
        if (msg == WM_MBUTTONUP) button = 2;
        io.MouseDown[button] = false;
        if (!ImGui::IsAnyMouseDown() && ::GetCapture() == hWnd)
            ::ReleaseCapture();
        return 0;
    }
    case WM_MOUSEWHEEL:
        io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
        return 0;
    case WM_MOUSEHWHEEL:
        io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
        return 0;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (wParam < 256)
            io.KeysDown[wParam] = 1;
        return 0;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        if (wParam < 256)
            io.KeysDown[wParam] = 0;
        return 0;
    case WM_CHAR:
        // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
        if (wParam > 0 && wParam < 0x10000)
            io.AddInputCharacter((unsigned short)wParam);
        return 0;
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT && ImGui_ImplWin32_UpdateMouseCursor())
            return 1;
        return 0;
    }

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
    DWORD style = /*WS_OVERLAPPEDWINDOW;*/ (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

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
    HINSTANCE hInstance = GetModuleHandle(nullptr);

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

    ImGui_ImplWin32_Init(m_Handle);
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
