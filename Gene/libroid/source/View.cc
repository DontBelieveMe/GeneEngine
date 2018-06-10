#include <libroid/View.h>

using namespace libroid;

View::View(JNIEnv* env, const jobject& obj) : JavaObject(env, obj) {
    jclass viewClass = env->FindClass("android/view/View");
    m_methodSetSystemUiVisibility = env->GetMethodID(viewClass, "setSystemUiVisibility", "(I)V");
}

void View::SetSystemUiVisibility(int visibility) {
    m_jnienv->CallVoidMethod(m_object, m_methodSetSystemUiVisibility, visibility);
}