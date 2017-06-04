#include <Platform/OS.h>
#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>
using namespace Gene::Input;

#if defined(GENE_OS_LINUX)
#include <X11/X.h>
MouseState &Mouse::GetState() {
//    static MouseState s;
    
    return s_PrimaryWindow->m_MouseState;
}

KeyboardState &Keyboard::GetState() {
    static KeyboardState s;
    return s;
}
#endif
