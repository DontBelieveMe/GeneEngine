#include <libroid/Window.h>

using namespace libroid;

const int WindowManager::LayoutParams::FLAG_FULLSCREEN = 0x00000400;

Window::Window(JNIEnv *env, const jobject& obj): JavaObject(env, obj) {
    jclass windowClass = env->FindClass("android/view/Window");
    m_methodGetDecorView = env->GetMethodID(windowClass, "getDecorView", "()Landroid/view/View;");
    m_methodSetFlags = env->GetMethodID(windowClass, "setFlags", "(II)V");
}

void Window::SetFlags(int flags, int mask) {
    m_jnienv->CallVoidMethod(m_object, m_methodSetFlags, flags, mask);
}

View Window::GetDecorView() {
    jobject decorView = m_jnienv->CallObjectMethod(m_object, m_methodGetDecorView);
    return View(m_jnienv, decorView);
}