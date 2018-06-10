#include <libroid/JavaObject.h>

using namespace libroid;

JavaObject::JavaObject(JNIEnv *env, const jobject& obj) : m_jnienv(env), m_object(obj) {
}