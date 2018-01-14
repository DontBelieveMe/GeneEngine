#pragma once

#include <string>
#include <GeneUI/PugiXML.hpp>

namespace GeneUI
{
    class DocumentParser
    {
    public:
        void Parse(const std::string& filepath);

        const pugi::xml_document& GetPugiDoc() const { return m_Document; }

    private:
        pugi::xml_document m_Document;
    };
}