#include <libroid/Activity.h>

using namespace libroid;

Activity::Activity(JNIEnv *env, const jobject& obj) : JavaObject(env, obj) {
    jclass activityClass = env->FindClass("android/app/NativeActivity");
    m_methodGetWindow = env->GetMethodID(activityClass, "getWindow", "()Landroid/view/Window;");
}

Window Activity::GetWindow() {
    jobject window = m_jnienv->CallObjectMethod(m_object, m_methodGetWindow);
    return Window(m_jnienv, window);
}

Activity Activity::GetNativeActivity(const JavaEnvironment& env) {
    return Activity(env.GetJNIEnv(), env.GetState()->activity->clazz);
}