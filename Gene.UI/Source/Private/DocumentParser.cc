#include "DocumentParser.hpp"

using namespace GeneUI;

void DocumentParser::Parse(const std::string & filepath)
{
    m_Document.load_file(filepath.c_str());
}
