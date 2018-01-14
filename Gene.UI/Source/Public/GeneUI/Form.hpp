#pragma once

#include <string>

#include <Platform/Window.h>

namespace GeneUI {
    class Form 
    {
    private:
        Gene::Platform::Window *m_Window;
    private:

    public:
        void LoadFromFile(std::string filename);

        void Show();

        void Destroy();
    };
}