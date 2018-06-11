#pragma once

#include <jni.h>

#include "deps/android_native_app_glue.h"

namespace libroid {
	class JavaEnvironment {
	    JNIEnv *m_jnienv;
	    struct android_app *m_state;

	public:
	    JavaEnvironment(struct android_app* state) {
	        m_state = state;
	        m_state->activity->vm->AttachCurrentThread(&m_jnienv, NULL);
	    }

	    ~JavaEnvironment() {
	        m_state->activity->vm->DetachCurrentThread();
	    }

	    struct android_app* GetState() const {
	        return m_state;
	    }

	    JNIEnv *GetJNIEnv() const {
	        return m_jnienv;
	    }
	};
}