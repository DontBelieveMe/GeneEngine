#include <libroid/View.h>

using namespace libroid;

const int View::SYSTEM_UI_FLAG_FULLSCREEN = 0x00000004;
const int View::SYSTEM_UI_FLAG_HIDE_NAVIGATION = 0x00000002;
const int View::SYSTEM_UI_FLAG_LAYOUT_STABLE = 0x00000100;
const int View::SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION = 0x00000200;
const int View::SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN = 0x00000400;
const int View::SYSTEM_UI_FLAG_IMMERSIVE_STICKY = 0x00001000;

View::View(JNIEnv* env, const jobject& obj) : JavaObject(env, obj) {
    jclass viewClass = env->FindClass("android/view/View");
    m_methodSetSystemUiVisibility = env->GetMethodID(viewClass, "setSystemUiVisibility", "(I)V");
}

void View::SetSystemUiVisibility(int visibility) {
    m_jnienv->CallVoidMethod(m_object, m_methodSetSystemUiVisibility, visibility);
}