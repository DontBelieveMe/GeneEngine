// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include "GLFLLoad.h"
#include <Platform/OpenGL.h>

using namespace Gene::Platform;

void GLFLUtil::GLFLInit(void*(*loader)(const char*))
{
    glfl::set_function_loader(loader);
    glfl::load_everything();
}
