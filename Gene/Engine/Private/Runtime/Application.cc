// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Runtime/Application.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace gene;

void App::Run(int windowW, int windowH, const char *title)
{
    platform::WindowInfo info;
    info.Width = windowW;
    info.Height = windowH;
    info.Title = title;

    m_window = platform::Window::CreateWindow(info);
    m_window->Create();
    m_window->SetClearColor(graphics::Color::Black);

    Init();

    platform::GameTime gameTimer;
    gameTimer.Start();
    m_window->Show();
    while (m_window->Running())
    {
        gameTimer.StartFrame();
        m_window->PollEvents();

        Tick(gameTimer);

        m_window->Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        Draw();

        ImGui::NewFrame();
        GuiDraw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window->SwapBuffers();

        gameTimer.EndFrame();

        if (m_fps > 0)
        {
            gameTimer.Sleep(1000.0f / m_fps);
        }
    }
}