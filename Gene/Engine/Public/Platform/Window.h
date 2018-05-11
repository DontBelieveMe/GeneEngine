// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/GLContext.h>
#include <Graphics/Color.h>

#include <Input/MouseState.h>
#include <Input/KeyboardState.h>

#include <Math/Vector2.h>

namespace Gene { namespace Input {
	class Mouse;
	class Keyboard;
}}

/* LOL, we define our own main. You know why? because fuck you. Yeah thats right. Fuck you. I run this shop */
// EDIT: Only joking I realise that sounds a bit abrasive - there is a reason. (I'm looking at you android)
// Until we redo the android native glue code we have to put up with their way of doing things and that includes
// a `void android_main(struct app_state*)` and not `int main()` so we will abstract it away in here
int GeneMain(int argc, char** argv);

namespace Gene { namespace Platform {

    /** Data about the window */
	struct WindowInfo
	{
        /** The width of the window in pixels. */
        int         Width;

        /** The height of the window in pixels. */
        int         Height;

        /** The title of the window */
		const char *Title;

        /** Should the window be borderless. This will remove any control box etc... */
        bool        Borderless = false;
	};

	struct EventCallbacks
	{
		void(*Resize)(int, int) = nullptr;
	};

    /** Base class that represents a window accross all platforms, capable of being drawn to and recieving input. */
	class Window
	{
	protected:
        WindowInfo            m_WindowConfig;
        GLContext            *m_Context;
        bool                  m_Running = true;
        Input::MouseState     m_MouseState;
        Input::KeyboardState  m_KeyState;
        EventCallbacks        m_Callbacks;

		friend class Input::Mouse;
        friend class Input::Keyboard;

	public:
        virtual ~Window() { delete m_Context; }
		Window(WindowInfo info);

        /** Creates the window itself but will not show it yet. Does initalize any graphics, use CreateGLContext for that */
		virtual void Create() = 0;

        /** Creates the OpenGL context, meaning it can now be drawn to. Should be called after Create() */
		virtual void CreateGLContext() = 0;

        /** Shows the window. */
		virtual void Show() = 0;

        /** Poll the event queue, checking for input and window modification events, such as close or resize. */
		virtual void PollEvents() = 0;

        /** Display buffer (basically draw shit to the screen) */
		virtual void SwapBuffers() = 0;

        /** Destroy any platform resources used by the window */
        virtual void Destroy() = 0;

        /** Converts global screen (moniter) coordinates to local window coordinates. */
		virtual Vector2 ScreenToWindow(const Vector2& point) = 0;

        /** Converts coordinates from local window coordinates to global screen (moniter) coordinates. */
		virtual Vector2 WindowToScreen(const Vector2& point) = 0;

        /** Retrieves the width of the window as specified in the WindowInfo */
        inline int        Width()        const { return m_WindowConfig.Width;  }

        /** Retrieves the height of the window as specified in the WindowInfo */
        inline int        Height()       const { return m_WindowConfig.Height; }

        /** Is the window open (running). This is based on the fact the window has not recieved any close event. */
        inline bool       Running()      const { return m_Running; }

        /** Returns a pointer to a platform agnostic OpenGL context representation. */
		inline GLContext *GetGLContext() const { return m_Context; }

        /** Set the callback to be called when the window is resized. */
        inline void SetWindowResizeCallback(void(*resize)(int, int))
            { m_Callbacks.Resize = resize;  }

        /** Creates a the platform window, based on the platform the code is being called from. (the platform defines) */
		static Window *CreateWindow(WindowInfo info);

        /** Set the graphical clear color of the window. The window will be reset to this color when Window::Clear is called */
		void SetClearColor(Graphics::Color color);

        /** Reset the window to the specified clear color. If no color has been specified by SetClearColor then it will reset to black. */
        void Clear();
    };
}}
