#pragma once

#include <Platform/GLContext.h>
#include <Graphics/Color.h>
#include <Input/MouseState.h>

namespace Gene { namespace Input {
	class Mouse;
}}

namespace Gene { namespace Platform {
	struct WindowInfo
	{
		int Width, Height;
		const char *Title;
	};

	struct EventCallbacks
	{
		void(*Resize)(int, int) = nullptr;
	};

	class Window
	{
	protected:
		WindowInfo m_WindowConfig;
		GLContext *m_Context;
		bool m_Running = true;
		Input::MouseState m_MouseState;
		EventCallbacks m_Callbacks;
		friend class Input::Mouse;

	public:
		virtual ~Window() { delete m_Context; };
		Window(WindowInfo info);

		virtual void Create() = 0;
		virtual void CreateGLContext() = 0;
		virtual void Show() = 0;
		virtual void PollEvents() = 0;
		virtual void SwapBuffers() = 0;
		
		inline unsigned Width()  const { return m_WindowConfig.Width;  }
		inline unsigned Height() const { return m_WindowConfig.Height; }
		inline bool Running() const { return m_Running; }
		inline GLContext *GetGLContext() const { return m_Context; }
		inline void SetWindowResizeCallback(void(*resize)(int,int)){ m_Callbacks.Resize = resize;  }

		static Window *CreateWindow(WindowInfo info);

		void SetClearColor(Graphics::Color color);
	};
}}