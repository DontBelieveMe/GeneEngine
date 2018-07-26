#pragma once

#include <Platform/OS.h>

#include "../../../Dependencies/imgui/imgui.h"
#include "../../../Dependencies/imgui/imgui_impl_opengl3.h"

#if defined(GENE_OS_WINDOWS)
    #include "../../../Dependencies/imgui/imgui_impl_win32.h"
#else
    #error ImGui not supported on non windows platform. Yet...
#endif

#include <Math/Vector3.h>
#include <Graphics/Color.h>
#include <memory>

namespace gene { namespace graphics {
    struct ImGuiHelpers {
        static void InputVector3(const char* str, Vector3 *vec)
        {
            ImGui::InputFloat3(str, &((*vec).X));
        }

        static void InputVector2(const char* str, Vector2 *vec)
        {
            ImGui::InputFloat2(str, &((*vec).X));
        }

        static void ColorPicker(const char* str, Color* col)
        {
            static float c[3];
            ImGui::ColorPicker3(str, c);
            unsigned int hex = Color::RGBAToHex(static_cast<int>(c[0]*255), static_cast<int>(c[1]*255), static_cast<int>(c[2]*255), 255);
            std::memcpy(col, &hex, sizeof(unsigned int));
        }
    };
}}