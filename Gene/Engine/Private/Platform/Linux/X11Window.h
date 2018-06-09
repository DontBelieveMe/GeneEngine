// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/Window.h>
#include <Platform/GLContext.h>
#include <Math/Vector2.h>
#include <GeneCommon.h>

namespace gene { namespace platform { namespace X11 {
    class X11Window : public gene::platform::Window
    {
    private:
        void *m_Display;
        void *m_VisualInfo;
        void *m_Window;

    public:
        virtual ~X11Window();
        X11Window(WindowInfo info) : gene::platform::Window(info) {}

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
