#pragma once

#include <Graphics/GLSLShader.h>
#include <vector>
#include <algorithm>

namespace Gene { namespace Graphics {
    struct ShaderAttributeLayout {
        int Index;
        const char *Name;
    };

    struct ShaderLayout {
        typedef std::initializer_list<ShaderAttributeLayout> InitalizerListLayout;


        std::vector<ShaderAttributeLayout> Attributes;

        template <typename... Args>
        ShaderLayout(Args... args) 
        {
            Attributes.push_back(args...);
        }

        ShaderLayout(InitalizerListLayout layout)
        {
            for (InitalizerListLayout::iterator it = layout.begin(); it != layout.end(); it++)
            {
                Attributes.push_back(*it);
            }
        }

        ShaderLayout() {}
    };

    class ShaderFactory {
    private:
        static std::vector<GLSLShader*> m_Handles;

    public:
        static GLSLShader *CreateShader(std::string vertexPath, std::string fragmentPath, ShaderLayout = ShaderLayout());

        static void FreeResources();
        
        static void FreeResource(int index);
        static void FreeResource(GLSLShader *shader);

        GLSLShader *operator[](int index);
        GLSLShader *AtIndex(int index);
    };
}}