#pragma once

#include <Platform/Window.h>
#include <Platform/GLContext.h>
#include <Math/Vector2.h>
#include <GeneCommon.h>

namespace Gene { namespace Platform { namespace X11 {
    class X11Window : public Gene::Platform::Window
    {
    private:
        void *m_Display;
        void *m_VisualInfo;
        void *m_Window;

        using Vector2 = Gene::Math::Vector2;
    public:
        virtual ~X11Window();
        X11Window(WindowInfo info) : Gene::Platform::Window(info) {}

        void Create() override;
        void CreateGLContext() override;
        void Show() override;
        void PollEvents() override;
        void SwapBuffers() override;
        void Destroy() override;

        Vector2 ScreenToWindow(const Vector2& point) override;
        Vector2 WindowToScreen(const Vector2& point) override;

        void SetPointerPosition(int32 x, int32 y);
    };
}}}
