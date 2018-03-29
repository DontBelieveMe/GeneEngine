// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>

#include "../../../../ThirdParty/android/android_native_app_glue.h"
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/sensor.h>

#include "AWindow.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Gene", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Gene", __VA_ARGS__))

using namespace Gene::Platform::Android;
using namespace Gene;

void *AWindow::s_AndroidAppState = nullptr;

static EGLDisplay s_Display;
static EGLSurface s_Surface;

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

static int32_t AndroidEngineHandleInput(struct android_app* app, AInputEvent* event)
{
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
	const EGLint attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(m_App->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, m_App->window, NULL);
	context = eglCreateContext(display, config, NULL, NULL);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOGW("Cannot make GLES context current!");
		return;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	m_Display = display;
	m_Context = context;
	m_Surface = surface;
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
