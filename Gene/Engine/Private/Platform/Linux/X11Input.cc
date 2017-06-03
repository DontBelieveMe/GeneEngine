#include <Platform/OS.h>
#include <Input/Mouse.h>
#include <Input/MouseState.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>

using namespace Gene::Input;
#if defined(GENE_OS_LINUX)
MouseState &Mouse::GetState() {
    static MouseState s;
    return s;
}

KeyboardState &Keyboard::GetState() {
    static KeyboardState s;
    return s;
}
#endif
