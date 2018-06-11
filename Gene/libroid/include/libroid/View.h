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
	    static const int SYSTEM_UI_FLAG_FULLSCREEN;
	    static const int SYSTEM_UI_FLAG_HIDE_NAVIGATION;
	    static const int SYSTEM_UI_FLAG_LAYOUT_STABLE;
	    static const int SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION;
	    static const int SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN;
	    static const int SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
	};
}