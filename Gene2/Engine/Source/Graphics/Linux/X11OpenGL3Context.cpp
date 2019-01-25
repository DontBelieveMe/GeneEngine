// Copright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Linux/X11OpenGL3Context.hpp>

using namespace g2::x11;

X11OpenGL3Context::X11OpenGL3Context(void* windowHandle)
	: IOpenGL3Context(windowHandle) {}

void X11OpenGL3Context::Create() {}

void X11OpenGL3Context::SwapBuffers(){}
