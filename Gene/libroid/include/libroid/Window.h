#pragma once

#include "View.h"

namespace libroid {
	class Window : protected JavaObject {
        jmethodID m_methodGetDecorView;
        jmethodID m_methodSetFlags;

    public:
        Window(JNIEnv *env, const jobject& obj);

        void SetFlags(int flags, int mask);
        View GetDecorView();
    };

    class WindowManager {
    public:
        struct LayoutParams {
            static const int FLAG_FULLSCREEN;
        };
    };
}