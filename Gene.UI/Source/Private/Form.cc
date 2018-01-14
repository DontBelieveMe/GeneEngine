#include <GeneUI/Form.hpp>
#include <GeneUI/PugiXML.hpp>

#include <GeneCommon.h>
#include <Graphics/Color.h>

#include "DocumentParser.hpp"

using namespace GeneUI;

#define CHECK_NODE_IS_TYPE(node, node_name) \
    GE_ASSERT(strcmp(node.name(), #node_name) == 0)

#define GET_ATTRIB(node, attrib_name) \
    node.attribute(#attrib_name)

void Form::LoadFromFile(std::string filename) 
{
    DocumentParser document;
    document.Parse(filename);

    const pugi::xml_document& pugiDoc = document.GetPugiDoc();

    pugi::xml_node windowNode = pugiDoc.first_child();
    
    CHECK_NODE_IS_TYPE(windowNode, Window);

    Gene::Platform::WindowInfo info;
    info.Title = GET_ATTRIB(windowNode, Title).as_string();
    info.Width = GET_ATTRIB(windowNode, Width).as_int();
    info.Height = GET_ATTRIB(windowNode, Height).as_int();

    m_Window = Gene::Platform::Window::CreateWindow(info);
    m_Window->Create();
    m_Window->CreateGLContext();
    m_Window->SetClearColor(Gene::Graphics::Color::CornflowerBlue);
}

void Form::Show() 
{
    m_Window->Show();
    while (m_Window->Running())
    {
        m_Window->Clear();

        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}

void Form::Destroy() 
{
    delete m_Window;
}