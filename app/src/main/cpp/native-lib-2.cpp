#include <jni.h>
#include <string>
#include <stdlib.h>
#include <android/log.h>


static const char *className = "com/huruwo/ndk_learn/MainActivity";

extern "C" JNIEXPORT jstring JNICALL
stringFromJNI_2(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from FromJNI_2 C++";
    return env->NewStringUTF(hello.c_str());
}

static const JNINativeMethod gMethods[] = {
        {"stringFromJNI_2", "()Ljava/lang/String;", (jstring *) stringFromJNI_2}
};


extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_ERROR, "LogX_JNI", "Jni_OnLoad");
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass clazz = env->FindClass(className);
    if (!clazz) {
        __android_log_print(ANDROID_LOG_ERROR, "LogX_JNI", "cannot get class: com/example/efan/jni_learn2/MainActivity");
        return -1;
    }
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0]))) {
        __android_log_print(ANDROID_LOG_ERROR, "LogX_JNI", "register native method failed!\n");
        return -1;
    }
    return JNI_VERSION_1_4;
}





