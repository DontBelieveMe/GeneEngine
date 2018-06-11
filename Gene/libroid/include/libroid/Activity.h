#pragma once

#include "JavaObject.h"
#include "Window.h"
#include "JavaEnvironment.h"

namespace libroid {
	class Activity : protected JavaObject {
        jmethodID m_methodGetWindow;

    public:
        Activity(JNIEnv *env, const jobject& obj);

        Window GetWindow();

        static Activity GetNativeActivity(const JavaEnvironment& env);
    };
}