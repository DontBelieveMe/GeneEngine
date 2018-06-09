// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace gene { namespace platform {
    struct GLFLUtil {
        static void GLFLInit(void*(*loader)(const char*));
    };
}}
