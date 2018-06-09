// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Graphics/GLSLShader.h>
#include <Core/Array.h>
#include <GeneCommon.h>

#include <algorithm>

namespace gene { namespace graphics {
    struct ShaderAttributeLayout {
        int Index;
        const char *Name;
    };

    struct ShaderLayout {
        typedef std::initializer_list<ShaderAttributeLayout> InitalizerListLayout;

        Array<ShaderAttributeLayout> Attributes;

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
        static Array<GLSLShader*> m_Handles;

    public:
        static GLSLShader *CreateShader(const String& vertexPath, const String& fragmentPath, ShaderLayout = ShaderLayout());

        static void FreeResources();
        
        static void FreeResource(int index);
        static void FreeResource(GLSLShader *shader);

        GLSLShader *operator[](int index);
        GLSLShader *AtIndex(int index);
    };
}}