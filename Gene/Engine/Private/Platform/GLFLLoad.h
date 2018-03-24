// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

namespace Gene { namespace Platform {
    struct GLFLUtil {
        static void GLFLInit(void*(*loader)(const char*));
    };
}}
