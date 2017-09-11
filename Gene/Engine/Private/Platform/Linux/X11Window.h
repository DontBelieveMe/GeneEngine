#pragma once

#include <Platform/Window.h>
#include <Platform/GLContext.h>
#include <GeneCommon.h>

namespace Gene { namespace Platform { namespace X11 {
    class X11Window : public Gene::Platform::Window
    {
    private:
        void *m_Display;
        void *m_VisualInfo;
        void *m_Window;
    public:
        virtual ~X11Window();
        X11Window(WindowInfo info) : Gene::Platform::Window(info) {}

        void Create() override;
        void CreateGLContext() override;
        void Show() override;
        void PollEvents() override;
        void SwapBuffers() override;
        void Destroy() override;

        void SetPointerPosition(int32 x, int32 y);
    };
}}}
