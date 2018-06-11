// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include "AWindow.h"
#include "../../../../ThirdParty/android/android_native_app_glue.h"

#include <android/log.h>
#include <android/sensor.h>

#include <Platform/OpenGL.h>
#include <Platform/OS.h>
#include <Math/Vector2.h>
#include <Input/Mouse.h>
#include <Input/Keyboard.h>

#include <libroid/libroid.h>

using namespace gene::platform::android;
using namespace gene;

void *AWindow::s_AndroidAppState = nullptr;

void GoFullscreen(struct android_app* state)
{
    using namespace libroid;

    JavaEnvironment environment(state);

    Activity activity = Activity::GetNativeActivity(environment);
    Window window = activity.GetWindow();
    
    window.SetFlags(
        WindowManager::LayoutParams::FLAG_FULLSCREEN, 
        WindowManager::LayoutParams::FLAG_FULLSCREEN
    );

    View view = window.GetDecorView();

    view.SetSystemUiVisibility(
          View::SYSTEM_UI_FLAG_LAYOUT_STABLE
        | View::SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
        | View::SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
        | View::SYSTEM_UI_FLAG_HIDE_NAVIGATION
        | View::SYSTEM_UI_FLAG_FULLSCREEN
        | View::SYSTEM_UI_FLAG_IMMERSIVE_STICKY
    );
}

static EGLDisplay s_Display;
static EGLSurface s_Surface;
static bool s_CreatedSurface;

static void AndroidEngineHandleCommand(struct android_app* app, int32_t cmd)
{
	struct AWindow* window = (AWindow*)app->userData;
		
	switch(cmd)
	{
	case APP_CMD_INIT_WINDOW:
		if(window->GetApp()->window != NULL)
		{
			window->CreateGLContext();
		}
		break;
	case APP_CMD_TERM_WINDOW:
		window->Destroy();
		break;
	}
}

int *_mouseX;
int *_mouseY;
input::MouseButton *_mButtonState;

static int32_t AndroidEngineHandleInput(struct android_app* app, AInputEvent* event)
{
    int32_t eventType = AInputEvent_getType(event);
    switch (eventType) {
    case AINPUT_EVENT_TYPE_MOTION:
        switch (AInputEvent_getSource(event)) {
        case AINPUT_SOURCE_TOUCHSCREEN:
            int action = AKeyEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
            switch (action) {
            case AMOTION_EVENT_ACTION_DOWN: {
                int x = AMotionEvent_getX(event, 0);
                int y = AMotionEvent_getY(event, 0);
                
                *_mouseX = x;
                *_mouseY = y;
                *_mButtonState = (input::MouseButton)(static_cast<unsigned>(*_mButtonState) | static_cast<unsigned>(input::MouseButton::Left));
                break;
            }
            case AMOTION_EVENT_ACTION_UP: {
                *_mouseX = -1;
                *_mouseY = -1;
                *_mButtonState = (input::MouseButton)(static_cast<unsigned>(*_mButtonState) & ~(static_cast<unsigned>(input::MouseButton::Left)));

                break;
            }
            case AMOTION_EVENT_ACTION_MOVE:
                break;
            }
            break;
        }
        break;
    case AINPUT_EVENT_TYPE_KEY:
        break;
    }
    return 0;
}

void AWindow::Create()
{
	m_Running = true;
	struct android_app* state = (struct android_app*)AWindow::s_AndroidAppState;
	
	state->userData = this;
	state->onAppCmd = AndroidEngineHandleCommand;
	state->onInputEvent = AndroidEngineHandleInput;
	m_App = state;
	GoFullscreen(state);

    input::Mouse::SetPrimaryWindow(this);
    input::Keyboard::SetPrimaryWindow(this);
    memset(m_KeyState.KeyMap, 0, 62256);
    m_MouseState.m_Button = gene::input::MouseButton::None;
    _mouseX = &(m_MouseState.m_Position.X);
    _mouseY = &(m_MouseState.m_Position.Y);
    _mButtonState = &(m_MouseState.m_Button);

	while(!s_CreatedSurface)
	{
		PollEvents();
	}	
}

AWindow::~AWindow()
{
}

void AWindow::Destroy()
{
}

void AWindow::SetPointerPosition(int32 x, int32 y)
{
}

void AWindow::CreateGLContext()
{
    LOG(LogLevel::Debug, "Creating Android OpenGL Context");
	const EGLint attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};
    
    const EGLint GiveMeGLES3[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };

	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    int err;
	err = eglInitialize(display, 0, 0);
    GE_ASSERT(err == EGL_TRUE);

	err = eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    GE_ASSERT(err == EGL_TRUE);

    err = eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    GE_ASSERT(err == EGL_TRUE);

	ANativeWindow_setBuffersGeometry(m_App->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, m_App->window, NULL);
	context = eglCreateContext(display, config, NULL, GiveMeGLES3);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOG(LogLevel::Error, "Cannot make GLES context current!");
		return;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	m_Display = display;
	m_Context = context;
	m_Surface = surface;
	s_CreatedSurface = true;

    LOG(LogLevel::Debug, "Screen Size: ", m_WindowConfig.Width, "x", m_WindowConfig.Height);

    m_WindowConfig.Width = w;
    m_WindowConfig.Height = h;

    glViewport(0, 0, w, h);
}

void AWindow::Show()
{
}

void AWindow::PollEvents()
{
	int ident, events;
	struct android_poll_source* source;
	
	while((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) 
	{
		if(source != NULL)
		{
			source->process(m_App, source);
		}

		if(m_App->destroyRequested != 0) 
		{
			Destroy();
			m_Running = false;
		}
	}
}

void AWindow::SwapBuffers()
{
	eglSwapBuffers(m_Display, m_Surface);
}

Vector2 AWindow::ScreenToWindow(const Vector2 &point)
{
}

Vector2 AWindow::WindowToScreen(const Vector2 &point)
{
}
