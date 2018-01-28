#pragma once

#include <GeneUI/Window.hpp>
#include <memory>

namespace GeneUI {
    class Application 
    {
    public:
        static void Run(const std::unique_ptr<Window>& window);
    };
}