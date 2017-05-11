#pragma once

namespace Gene { namespace Platform {
    struct GLFLUtil {
        static void GLFLInit(void*(*loader)(const char*));
    };
}}
