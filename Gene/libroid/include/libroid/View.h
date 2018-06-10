#pragma once

#include "JavaObject.h"

namespace libroid {
	class View : protected JavaObject {
	private:
	    jmethodID m_methodSetSystemUiVisibility;

	public:
	    View(JNIEnv* env, const jobject& obj);

	    void SetSystemUiVisibility(int visibility);

	public:
	    static const int SYSTEM_UI_FLAG_FULLSCREEN = 0x00000004;
	    static const int SYSTEM_UI_FLAG_HIDE_NAVIGATION = 0x00000002;
	    static const int SYSTEM_UI_FLAG_LAYOUT_STABLE = 0x00000100;
	    static const int SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION = 0x00000200;
	    static const int SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN = 0x00000400;
	    static const int SYSTEM_UI_FLAG_IMMERSIVE_STICKY = 0x00001000;
	};
}