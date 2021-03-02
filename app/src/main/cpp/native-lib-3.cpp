#include <jni.h>
#include <string>
#include "md5.h"

char *join3(char *, char *);

#define MD5_KEY  "123456"

extern "C" JNIEXPORT jstring JNICALL
Java_com_huruwo_ndk_1learn_MainActivity_stringFromJNI_13(
        JNIEnv* env,
        jobject /* this */) {
    //尝试反向调用java层的方法 获取数据
    auto JavaTools = env->FindClass("com/huruwo/ndk_learn/JavaTools");

    //https://github.com/CB2Git/BlogDemoRepository/blob/master/NDKFirst/app/src/main/cpp/ndk_test.cpp

    //auto stringFromJava1 = (env)->GetStaticMethodID(JavaTools, "stringFromJava1", "()Ljava/lang/String;");
    //auto str1 = (env)->CallStaticObjectMethod(JavaTools, stringFromJava1);


    //auto stringFromJava2 = (env)->GetStaticMethodID(JavaTools, "stringFromJava2","(Ljava/lang/String;)Ljava/lang/String;");
    //auto str2 = (env)->CallStaticObjectMethod(JavaTools, stringFromJava2,env->NewStringUTF("测试调用"));


    //auto stringFromJava3 = (env)->GetStaticMethodID(JavaTools, "stringFromJava3", "()V");
    //(env)->CallStaticVoidMethod(JavaTools, stringFromJava3);


    //实例化类 调用
    auto stringFromJava4 = (env)->GetMethodID(JavaTools, "stringFromJava4","(Ljava/lang/String;)Ljava/lang/String;");

    // Java构造方法的实例化
    const char *sig = "()V";
    const char *method = "<init>"; // Java构造方法的标识
    auto init = env->GetMethodID(JavaTools, method, sig);
    auto jsob = env->NewObject(JavaTools, init);
    auto str4 = (env)->CallObjectMethod(jsob, stringFromJava4,env->NewStringUTF("测试调用"));



    return (jstring)str4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_huruwo_ndk_1learn_MainActivity_encryptMD5(
        JNIEnv* env,
        jobject /* this */,jstring str) {


    const char *originStr;
    //将jstring转化成char *类型
    originStr = env->GetStringUTFChars(str, false);
    MD5 md5 = MD5(originStr);
    std::string md5Result = md5.hexdigest();
    //将char *类型转化成jstring返回给Java层
    return env->NewStringUTF(md5Result.c_str());


}

