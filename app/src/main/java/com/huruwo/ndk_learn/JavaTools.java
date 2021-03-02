package com.huruwo.ndk_learn;

import android.util.Log;

public class JavaTools {

    private String name;

    public JavaTools() {
    }

    public JavaTools(String name) {
        this.name = name;
    }

    private static String stringFromJava1(){
        return "stringFromJava1";
    }

    private static String stringFromJava2(String str){
        return "stringFromJava2"+str;
    }

    private static void stringFromJava3(){
        Log.e("JavaTools","stringFromJava3");
    }

    private String stringFromJava4(String str){
        return "stringFromJava4"+str;
    }

}
