#include "../Menu/Jni.hpp"
#include "../Menu/Menu.hpp"
#include "../Includes/Utils.hpp"
#include <jni.h>

void Init(JNIEnv *env, jobject thiz, jobject ctx, jobject title, jobject subtitle) {
    //Set sub title
    if (strcmp(ENV_VERSION, "nightly") == 0)
        setText(env, title, "<b>NROIPChanger Nightly</b>");
    else 
        setText(env, title, "<b>NROIPChanger v" ENV_VERSION "</b>");

    //Set sub title
    setText(env, subtitle, "<b><marquee><p style=\"font-size:30\">"
        "<p style=\"color:green;\">Created by ElectroHeavenVN - Template from LGL</p> | "
        "https://github.com/ElectroHeavenVN/NROIPChanger</p> | "
        "<p style=\"color:red;\">Do not install from other sources!</p>"
        "</marquee></b>");

    //Dialog Example
    //setDialog(ctx,env,"Title","Message Example");

    //Toast Example
    //Toast(env, ctx, "Modded by YOU", ToastLength::LENGTH_LONG);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {"Icon", "()Ljava/lang/String;", reinterpret_cast<void*>(Icon)},
        {"IconWebViewData", "()Ljava/lang/String;", reinterpret_cast<void*>(IconWebViewData)},
        {"IsGameLibLoaded", "()Z", reinterpret_cast<void*>(isGameLibLoaded)},
        {"Init", "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", reinterpret_cast<void *>(Init)},
        {"SettingsList", "()[Ljava/lang/String;", reinterpret_cast<void*>(SettingsList)},
        {"GetFeatureList", "()[Ljava/lang/String;", reinterpret_cast<void*>(GetFeatureList)},
    };

    jclass clazz = env->FindClass("com/ehvn/nroipchanger/Menu");
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {"Changes", "(Landroid/content/Context;ILjava/lang/String;IJZLjava/lang/String;)V", reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass("com/ehvn/nroipchanger/Preferences");
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {"CheckOverlayPermission", "(Landroid/content/Context;)V", reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass("com/ehvn/nroipchanger/Main");
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}