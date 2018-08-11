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
        	ImGui::DragFloat3(str, &((*vec).X));
        }

        static void InputVector2(const char* str, Vector2 *vec)
        {
            ImGui::InputFloat2(str, &((*vec).X));
        }

        static void ColorPicker(const char* str, Color* col)
        {
			static float c[3] = {
				-1,-1,-1
			};

			ImGui::ColorEdit3(str, c);

            unsigned int hex = Color::RGBAToHex(static_cast<int>(c[0]*255), static_cast<int>(c[1]*255), static_cast<int>(c[2]*255), 255);
            std::memcpy(col, &hex, sizeof(unsigned int));
        }

		static void TextEdit(const char* str, std::string* str2)
		{
		}
		static void ReflectFromType(void* obj, gene::reflection::DataType* type, gene::reflection::Member* parentMember=nullptr)
		{
			ImGui::StyleColorsClassic();
			if (ImGui::CollapsingHeader(type->Name)) {
				ImGui::PushID(type->Name);
				for (gene::reflection::Member& member : type->Members) {
					ImGui::BeginGroup();
					ImGui::Indent();
					ImGui::Columns(2);
					ImGui::Text(member.Name);
					ImGui::NextColumn();
					if (member.Type == META_GET_DATA(gene::Vector3)) {
						InputVector3(member.Name, member.GetValueFromVoidPointer<gene::Vector3>(obj));
					}
					else if (member.Type == META_GET_DATA(gene::graphics::Color)) {
						ColorPicker(member.Name, member.GetValueFromVoidPointer<gene::graphics::Color>(obj));
					}
					else if (member.Type == META_GET_DATA(int)) {
						ImGui::DragInt(member.Name, member.GetValueFromVoidPointer<int>(obj));
					}
					else {
						ImGui::Columns(1);
						ReflectFromType(member.GetValueFromVoidPointer<void*>(obj), member.Type, &member);
					}
					ImGui::Columns(1);
					ImGui::Unindent();
					ImGui::Spacing();
					ImGui::EndGroup();
				}
				ImGui::PopID();
			}
		}

		template <typename T>
		static void ReflectObject(T* object)
		{
			gene::reflection::DataType* objType = META_GET_DATA(T);
			ReflectFromType(object, objType);
		}

	private:
    };
}}