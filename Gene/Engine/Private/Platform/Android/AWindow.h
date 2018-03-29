// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/Window.h>
#include <Platform/GLContext.h>
#include <Math/Vector2.h>
#include <GeneCommon.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "../../../../ThirdParty/android/android_native_app_glue.h"

namespace Gene { namespace Platform { namespace Android {
    class AWindow : public Gene::Platform::Window
    {
    private:
        struct android_app* m_App;

        EGLDisplay m_Display;
        EGLSurface m_Surface; 
        EGLContext m_Context;
        int32_t width;
        int32_t height;
        
    public:
        virtual ~AWindow();
        AWindow(WindowInfo info) : Gene::Platform::Window(info) {}

        void Create() override;
        void CreateGLContext() override;
        void Show() override;
        void PollEvents() override;
        void SwapBuffers() override;
        void Destroy() override;

        Vector2 ScreenToWindow(const Vector2& point) override;
        Vector2 WindowToScreen(const Vector2& point) override;

        void SetPointerPosition(int32 x, int32 y);

        static void* s_AndroidAppState;

        EGLDisplay GetDisplay() { return m_Display; }
        EGLSurface GetSurface() { return m_Surface; }
        EGLContext GetContext() { return m_Context; }
        struct android_app* GetApp() { return m_App; }
    };
}}}
