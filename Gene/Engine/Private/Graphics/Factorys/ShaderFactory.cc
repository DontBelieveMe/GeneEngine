#include <Graphics/Factorys/ShaderFactory.h>
#include <GeneCommon.h>

#include <Core/Array.h>

using namespace Gene::Graphics;
using namespace Gene;

Array<GLSLShader*> ShaderFactory::m_Handles;

GLSLShader *ShaderFactory::CreateShader(std::string vertexPath, std::string fragmentPath, ShaderLayout layout)
{
    GLSLShader *shader = new GLSLShader();
    shader->CompileFromFiles(vertexPath, fragmentPath);
    shader->Enable();
    
    for (const ShaderAttributeLayout& attrib : layout.Attributes)
    {
        shader->BindAttributeIndex(attrib.Index, attrib.Name);
    }

    shader->Disable();

    m_Handles.push_back(shader);
    return shader;
}

void ShaderFactory::FreeResources()
{
    for (GLSLShader*& shader : m_Handles) 
    {
        FreeResource(shader);
    }
}

void ShaderFactory::FreeResource(GLSLShader *shader)
{
    delete shader;
}

GLSLShader * ShaderFactory::operator[](int index)
{
    return AtIndex(index);
}

GLSLShader *ShaderFactory::AtIndex(int index)
{
    return m_Handles[index];
}

void ShaderFactory::FreeResource(int index)
{
    GLSLShader *value = m_Handles[index];
    FreeResource(value);
}
