#pragma once
#ifndef EHVNUTILS_H
#define EHVNUTILS_H

#include "AetherimMod/api.hpp"
#include "IL2CPP/il2cpp.h"
#include "Includes/Logger.h"
#include "Includes/Macros.h"
#include "Includes/Utils.h"
#include "utfcpp/utf8.h"
#include <jni.h>

#define HOOK_BY_NAME(n) if (n##_address != 0) HOOK_ADDR(reinterpret_cast<DWORD>(n##_address), n##_hook, n##_original)
#define targetLibName "libil2cpp.so"

static jstring GetPackageName(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getPackageName = env->GetMethodID(activityClass, "getPackageName", "()Ljava/lang/String;");
    jstring packageName = (jstring) env->CallObjectMethod(activity, getPackageName);
    return packageName;
}

static void ShowToastOnUIThread(JNIEnv* env, jclass declaringType, jstring content, int duration)
{
    jmethodID showToastOnUIThread = env->GetStaticMethodID(declaringType, "ShowToastOnUIThread", "(Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(declaringType, showToastOnUIThread, content, duration);
}

static void ShowToastOnUIThread(JavaVM* jvm, jclass declaringType, const char* content, int duration)
{
    JNIEnv* env;
    if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        return;
    jstring jstr = env->NewStringUTF(content);
    ShowToastOnUIThread(env, declaringType, jstr, duration);
    jvm->DetachCurrentThread();
}

static void ShowToastOnUIThread(JavaVM* jvm, jclass declaringType, std::string content, int duration)
{
    ShowToastOnUIThread(jvm, declaringType, content.c_str(), duration);
}

static std::string ToStdString(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";
    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));
    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

static bool StartsWith(System_String_o* str, const wchar_t* prefix) {
    if (str == nullptr)
        return false;
    size_t prefixLength = wcslen(prefix);
    if (prefixLength > str->fields.m_stringLength) {
        return false;
    }
    for (int i = 0; i < prefixLength; ++i) {
        if (prefix[i] != (&str->fields.m_firstChar)[i])
            return false;
    }
    return true;
}

static bool Equals(System_String_o* str1, const wchar_t* str2) {
    if (str1 == nullptr)
        return false;
    if (wcslen(str2) != str1->fields.m_stringLength) {
        return false;
    }
    for (int i = 0; i < str1->fields.m_stringLength; ++i) {
        if (str2[i] != (&str1->fields.m_firstChar)[i])
            return false;
    }
    return true;
}

System_String_o* CreateNetString(const char* str)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf8(str));
}

System_String_o* CreateNetString(const wchar_t* str)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf16(str, wcslen(str)));
}

static std::wstring GetStdWStr(System_String_o* str)
{
    return std::wstring(&str->fields.m_firstChar, &str->fields.m_firstChar + str->fields.m_stringLength);
}

static std::string GetStdStr(System_String_o* str)
{
	std::u16string u16str(&str->fields.m_firstChar, &str->fields.m_firstChar + str->fields.m_stringLength);
    return utf8::utf16to8(u16str);
}

static System_String_o* CreateNetString(std::string str)
{
	return CreateNetString(str.c_str());
}

static System_String_o* CreateNetString(std::wstring str)
{
	return CreateNetString(str.c_str());
}
#endif //EHVNUTILS_H
