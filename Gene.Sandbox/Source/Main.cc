
#include "../../Gene/ThirdParty/android/android_native_app_glue.h"
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))

extern "C" {
	struct saved_state {
		float angle;
		int32_t x;
		int32_t y;
	};

	struct engine {
		struct android_app* app;

		ASensorManager* sensorManager;
		const ASensor* accelerometerSensor;
		ASensorEventQueue* sensorEventQueue;

		int animating;
		EGLDisplay display;
		EGLSurface surface; 
		EGLContext context;
		int32_t width;
		int32_t height;
		struct saved_state state;
	};

	static int engine_init_display(struct engine* engine) {
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

		ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

		surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
		context = eglCreateContext(display, config, NULL, NULL);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
			LOGW("Unable to eglMakeCurrent");
			return -1;
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		engine->display = display;
		engine->context = context;
		engine->surface = surface;
		engine->width = w;
		engine->height = h;
		engine->state.angle = 0;

		// Initialize GL state.
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
		glEnable(GL_CULL_FACE);
		//glShadeModel(GL_SMOOTH);
		glDisable(GL_DEPTH_TEST);

		return 0;
	}

	static void engine_draw_frame(struct engine* engine) {
		if (engine->display == NULL) {
			return;
		}
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		const GLfloat triangleVertices[] = {
			0.0f,   0.5f,   0.0f,
			-0.5f,  -0.5f,  0.0f,
			0.5f,   -0.5f,  0.0f
		};
		
		glColor4f(8.0f, 3.0f, 0.5f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	}

	static void engine_term_display(struct engine* engine) {
		if (engine->display != EGL_NO_DISPLAY) {
			eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if (engine->context != EGL_NO_CONTEXT) {
				eglDestroyContext(engine->display, engine->context);
			}
			if (engine->surface != EGL_NO_SURFACE) {
				eglDestroySurface(engine->display, engine->surface);
			}
			eglTerminate(engine->display);
		}
		engine->animating = 0;
		engine->display = EGL_NO_DISPLAY;
		engine->context = EGL_NO_CONTEXT;
		engine->surface = EGL_NO_SURFACE;
	}

	static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
		return 0;
	}

	static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
		struct engine* engine = (struct engine*)app->userData;
		switch (cmd) {
		case APP_CMD_INIT_WINDOW:
			// The window is being shown, get it ready.
			if (engine->app->window != NULL) {
				engine_init_display(engine);
				engine_draw_frame(engine);
			}
			break;
		case APP_CMD_TERM_WINDOW:
			// The window is being hidden or closed, clean it up.
			engine_term_display(engine);
			break;
		}
	}

	static struct android_app* s_App;

	struct Window {
		void Create(struct engine& engine) {
			Running = true;
			struct android_app* state = s_App;

			state->userData = &engine;
			state->onAppCmd = engine_handle_cmd;
			state->onInputEvent = engine_handle_input;
			engine.app = state;

			engine.animating = 1;
		}

		void PollEvents(struct engine& engine) {
			int ident, events;
			struct android_poll_source* source;
			while((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
				if(source != NULL) {
					source->process(s_App, source);
				}

				if(s_App->destroyRequested != 0) {
					engine_term_display(&engine);
					Running = false;
				}
			}
		}

		void SwapBuffers(struct engine& engine) {
			eglSwapBuffers(engine.display, engine.surface);
		}

		bool Running;
	};

	void GeneMain() {
		struct android_app* state = s_App;

		struct engine engine;

		Window window;
		window.Create(engine);

		// loop waiting for stuff to do.

		while (window.Running) {
			window.PollEvents(engine);

			if (engine.animating) {
				// Done with events; draw next animation frame.
				engine.state.angle += .01f;
				if (engine.state.angle > 1) {
					engine.state.angle = 0;
				}

				// Drawing is throttled to the screen update rate, so there
				// is no need to do timing here.
				engine_draw_frame(&engine);
				window.SwapBuffers(engine);
			}
		}
	}

	void android_main(struct android_app* state) {
		s_App = state;
		GeneMain();	
	}
}

/*
#include <Platform/Window.h>
#include <Graphics/Color.h>

int GeneMain(int argc, char **argv)
{
    using namespace Gene::Platform;
    using namespace Gene::Graphics;
    using namespace Gene;
    
    WindowInfo info;
    info.Width = 800;
    info.Height = 600;
    info.Title = "Hello from GeneEngine.Sandbox";
    info.Borderless = false;

    Window *window = Window::CreateWindow(info);
    
    window->Create();
    window->CreateGLContext();
    
    window->Show();
    while (window->Running())
    {
    	window->PollEvents();
		
		//window->SetClearColor(Color::Red);

    	//window->SwapBuffers();  
    }
    return 0;
}*/