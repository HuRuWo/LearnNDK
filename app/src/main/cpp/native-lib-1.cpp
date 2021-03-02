#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_huruwo_ndk_1learn_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from FromJNI C++";
    return env->NewStringUTF(hello.c_str());
}