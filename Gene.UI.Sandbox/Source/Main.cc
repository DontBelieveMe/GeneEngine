#include <GeneUI/Form.hpp>

int main() 
{
    GeneUI::Form form;
    form.LoadFromFile("Forms/Main.xml");
    form.Show();
    form.Destroy();
}