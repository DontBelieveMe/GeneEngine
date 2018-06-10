#pragma once

#include <jni.h>

namespace libroid {
    class JavaObject {
    protected:
        JNIEnv * m_jnienv;
        jobject  m_object;

        JavaObject(JNIEnv *env, const jobject& obj);
    };
}