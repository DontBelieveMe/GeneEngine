#pragma once

#include <Platform/Window.h>
#include <Platform/GLContext.h>

namespace Gene { namespace Platform { namespace Win32 {
	class Win32Window : public Window
	{
	private:
		void *m_Handle;

	public:
		virtual ~Win32Window();
		Win32Window(WindowInfo info) : Window(info) {}

		void Create()	       override;
		void CreateGLContext() override;
		void Show()			   override;
        void PollEvents()      override;
		void SwapBuffers()	   override;
        void Destroy()         override;
	};
}}}
