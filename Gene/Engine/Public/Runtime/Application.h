// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Graphics/Color.h>
#include <Platform/Window.h>
#include <Platform/Time.h>

namespace gene {
    class App {
    public:
        App() : m_fps(60), m_window(nullptr) {}

        virtual void Init() {}
        virtual void Tick(const platform::GameTime& time) {}
        virtual void Draw() {}

        virtual void GuiDraw() {}

        void Run(int windowW, int windowH, const char *title);

    protected:
        platform::Window *GetWindow() { return m_window; }
        void SetTargetFPS(float fps) { m_fps = fps; }
        float GetTargetFPS(float fps) { return m_fps; }

    private:
        platform::Window *m_window;
        float m_fps;
    };
}