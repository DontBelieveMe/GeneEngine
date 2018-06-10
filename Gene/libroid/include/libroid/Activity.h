#pragma once

#include "JavaObject.h"
#include "Window.h"

namespace libroid {
	class Activity : protected JavaObject {
        jmethodID m_methodGetWindow;

    public:
        Activity(JNIEnv *env, const jobject& obj);

        Window GetWindow();
    };
}