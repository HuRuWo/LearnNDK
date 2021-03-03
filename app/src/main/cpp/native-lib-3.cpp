#include <jni.h>
#include <string>
#include "md5.h"



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


void setChar(int *arg1) {

    switch (*arg1) {
        case 10:
            *arg1 = 97;
            break;
        case 11:
            *arg1 = 98;
            break;
        case 12:
            *arg1 = 99;
            break;
        case 13:
            *arg1 = 100;
            break;
        case 14:
            *arg1 = 101;
            break;
        case 15:
            *arg1 = 102;
            break;
        default:
            *arg1 = *arg1 + 48;
            break;
    }
}

char * transformChar(unsigned char *arg) {
    char enstr[33];
    char *dest_str;
    for (int i = 0; i < 16; ++i) {
        int c1 = arg[i] / 16;
        setChar(&c1);
        int c2 = arg[i] % 16;
        setChar(&c2);
        char c3 = c1;
        char c4 = c2;
        enstr[i * 2] = c3;
        enstr[i * 2 + 1] = c4;
    }
    enstr[32] = '\0';
    dest_str = (char *) calloc(sizeof(enstr), sizeof(char));
    // dest_str = (char *)malloc(sizeof(char) * (sizeof(enstr)));

    /* 为字符串分配堆空间 */
    strncpy(dest_str, enstr, sizeof(enstr));
    // 用C标准库函数strncpy拷贝字符
    return dest_str;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_huruwo_ndk_1learn_MainActivity_encryptMD5(
        JNIEnv* env,
        jobject /* this */,jstring str) {


    MD5_CTX md5;
    MD5Init(&md5);
    auto encrypt = env->GetStringUTFChars(str, JNI_FALSE);
    unsigned char decrypt[16];
    MD5Update(&md5, (unsigned char *) encrypt, strlen((char *) encrypt));
    MD5Final(&md5, decrypt);
    //定义需要返回的char*
    char *md5str;
    //将加密后的unsigned char数组转化为char* 返回
    md5str = transformChar(&decrypt[0]);
    free(md5str);
    return env->NewStringUTF(md5str);


}



