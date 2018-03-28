// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>

#include "../../../../ThirdParty/android/android_native_app_glue.h"
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>

#include "AWindow.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Gene", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Gene", __VA_ARGS__))

using namespace Gene::Platform::Android;
using namespace Gene;

void *AWindow::s_AndroidAppState = nullptr;

static EGLDisplay s_Display;
static EGLSurface s_Surface;

extern "C" {
	static void AndroidEngineCreateGL()
	{
		struct android_app* app = (struct android_app*) AWindow::s_AndroidAppState;
		LOGW("Hello!");
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

		ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

		surface = eglCreateWindowSurface(display, config, app->window, NULL);
		context = eglCreateContext(display, config, NULL, NULL);

		// TODO: Error checking on this
		eglMakeCurrent(display, surface, surface, context);
		
		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		s_Display = display;
		s_Surface = surface;
	}

	static void AndroidEngineHandleCommand(struct android_app* app, int32_t cmd)
	{
		switch(cmd)
		{
		case APP_CMD_INIT_WINDOW:
			AndroidEngineCreateGL();
			break;
		}
	}

	static int32_t AndroidEngineHandleInput(struct android_app* app, AInputEvent* event)
	{
	}

}

void AWindow::Create()
{
	LOGW("Hello!");
	struct android_app* app = (struct android_app*) AWindow::s_AndroidAppState;
	app->onAppCmd = AndroidEngineHandleCommand;
	app->onInputEvent = AndroidEngineHandleInput;
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
}

void AWindow::Show()
{
}

void AWindow::PollEvents()
{
	// TODO: Debugging idea -> Maybe it is that the AWindow::Create android_app* is not the same as the one referred to here
	// or Create() is not setting the variables etc..
	int ident, events;
	struct android_poll_source* source;
	struct android_app* app = (struct android_app*) AWindow::s_AndroidAppState;
	
	while((ident = ALooper_pollAll(0, NULL, &events,
			(void**)&source)) >= 0)
	{
		LOGW("Looping!");
		if(source != NULL)
		{
			LOGW("Processing!");
			source->process(app, source);
		}

		if(app->destroyRequested != 0)
		{
			m_Running = false;
		}
	}
}

void AWindow::SwapBuffers()
{
	eglSwapBuffers(s_Display, s_Surface);
}

Vector2 AWindow::ScreenToWindow(const Vector2 &point)
{
}

Vector2 AWindow::WindowToScreen(const Vector2 &point)
{
}
