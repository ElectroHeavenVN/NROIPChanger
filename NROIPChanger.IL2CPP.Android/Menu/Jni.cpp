
#include "Jni.hpp"
#include <list>
#include <vector>
#include <cstring>
#include <string>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include "../Includes/get_device_api_level_inlines.h"
#include "../Includes/Logger.h"

//Jni stuff from MrDarkRX https://github.com/MrDarkRXx/DarkMod-Floating
void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg){
    jclass Alert = env->FindClass("android/app/AlertDialog$Builder");
    jmethodID AlertCons = env->GetMethodID(Alert, "<init>", "(Landroid/content/Context;)V");

    jobject MainAlert = env->NewObject(Alert, AlertCons, ctx);

    jmethodID setTitle = env->GetMethodID(Alert, "setTitle", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setTitle, env->NewStringUTF(title));

    jmethodID setMsg = env->GetMethodID(Alert, "setMessage", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setMsg, env->NewStringUTF(msg));

    jmethodID setCa = env->GetMethodID(Alert, "setCancelable", "(Z)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setCa, false);

    jmethodID setPB = env->GetMethodID(Alert, "setPositiveButton", "(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setPB, env->NewStringUTF("Ok"), static_cast<jobject>(NULL));

    jmethodID create = env->GetMethodID(Alert, "create", "()Landroid/app/AlertDialog;");
    jobject creaetob = env->CallObjectMethod(MainAlert, create);

    jclass AlertN = env->FindClass("android/app/AlertDialog");

    jmethodID show = env->GetMethodID(AlertN, "show", "()V");
    env->CallVoidMethod(creaetob, show);
}

void Toast(JNIEnv* env, jobject context, jstring text, int duration) {
    jclass toast = env->FindClass("android/widget/Toast");
    jmethodID methodMakeText = env->GetStaticMethodID(toast, "makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText, context, text, duration);
    jmethodID methodShow = env->GetMethodID(toast, "show", "()V");
    env->CallVoidMethod(toastobj, methodShow);
}

void Toast(JNIEnv* env, jobject context, const char* text, int duration) {
    jstring jstr = env->NewStringUTF(text);
    Toast(env, context, jstr, duration);
}

void Toast(JNIEnv* env, jobject context, const wchar_t* text, int duration) {
    jstring jstr = env->NewString((uint16_t*)text, wcslen(text));
    Toast(env, context, jstr, duration);
}

void startService(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jclass intentClass = env->FindClass("android/content/Intent");
    jclass actionString = env->FindClass("com/ehvn/nroipchanger/Launcher");
    jmethodID newIntent = env->GetMethodID(intentClass, "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V");
    jobject intent = env->NewObject(intentClass,newIntent,ctx,actionString);
    jmethodID startActivityMethodId = env->GetMethodID(native_context, "startService", "(Landroid/content/Intent;)Landroid/content/ComponentName;");
    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}

void *exit_thread(void *) {
    sleep(5);
    exit(0);
}

void startActivityPermisson(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jmethodID startActivity = env->GetMethodID(native_context, "startActivity","(Landroid/content/Intent;)V");

    jmethodID pack = env->GetMethodID(native_context, "getPackageName","()Ljava/lang/String;");
    jstring packageName = static_cast<jstring>(env->CallObjectMethod(ctx, pack));

    const char *pkg = env->GetStringUTFChars(packageName, 0);

    std::stringstream strpkg;
    strpkg << "package:";
    strpkg << pkg;
    std::string pakg = strpkg.str();

    jclass Uri = env->FindClass("android/net/Uri");
    jmethodID Parce = env->GetStaticMethodID(Uri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jobject UriMethod = env->CallStaticObjectMethod(Uri, Parce, env->NewStringUTF(pakg.c_str()));

    jclass intentclass = env->FindClass("android/content/Intent");
    jmethodID newIntent = env->GetMethodID(intentclass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");
    jobject intent = env->NewObject(intentclass,newIntent,env->NewStringUTF("android.settings.action.MANAGE_OVERLAY_PERMISSION"), UriMethod);

    env->CallVoidMethod(ctx, startActivity, intent);
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass thiz, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jmethodID startActivity = env->GetMethodID(native_context, "startActivity", "(Landroid/content/Intent;)V");
    jmethodID pack = env->GetMethodID(native_context, "getPackageName", "()Ljava/lang/String;");
    jstring packageName = static_cast<jstring>(env->CallObjectMethod(ctx, pack));
    const char* pkg = env->GetStringUTFChars(packageName, 0);
    LOGI("Package name: %s", pkg);

    LOGI("Check overlay permission");

    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest

    int sdkVer = api_level();
    if (sdkVer >= 23){ //Android 6.0
        jclass Settings = env->FindClass("android/provider/Settings");
        jmethodID canDraw =env->GetStaticMethodID(Settings, "canDrawOverlays", "(Landroid/content/Context;)Z");
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)) {
            
			jclass strings = env->FindClass("com/ehvn/nroipchanger/Strings");
			jmethodID overlayNotificationMethod = env->GetStaticMethodID(strings, "overlayNotification", "()Ljava/lang/String;");
			jstring overlayNotification = static_cast<jstring>(env->CallStaticObjectMethod(strings, overlayNotificationMethod));

            Toast(env, ctx, overlayNotification, 1);
            startActivityPermisson(env, ctx);

            pthread_t ptid;
            pthread_create(&ptid, NULL, exit_thread, NULL);
            return;
        }
    }

    LOGI("Start service");

    //StartMod Normal
    startService(env, ctx);
}