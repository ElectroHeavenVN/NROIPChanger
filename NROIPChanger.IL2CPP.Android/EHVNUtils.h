#pragma once
#ifndef EHVNUTILS_H
#define EHVNUTILS_H

#include "IL2CPP/il2cpp.h"
#include "Includes/Logger.h"
#include "Includes/Macros.h"
#include "Includes/Utils.hpp"
#include "utfcpp/utf8.h"
#include <cwchar>
#include <jni.h>

#define HOOK_BY_NAME(n) if (n##_address != 0) HOOK(targetLibName, n##_address, n##_hook, n##_original)
#define targetLibName "libil2cpp.so"

System_String_o* (*System_String__CreateString_utf16)(void* instance, const wchar_t* value, int startIndex, int length, const MethodInfo*);
System_String_o* (*System_String__CreateString_utf8)(void* instance, const char* value, int startIndex, int length, const MethodInfo*);

static JavaVM* jvm;
static jclass preferencesClass;
static jclass utilsClass;
static jclass stringsClass;

static std::string ToStdString(JNIEnv * env, jstring jStr);

static bool AssignCreateStringUTF16(std::string addrStr) {
	if (addrStr.empty())
		return false;
	int offset = stoul(addrStr, nullptr, 16);
	if (offset == 0)
		return false;
    System_String__CreateString_utf16 = reinterpret_cast<System_String_o * (*)(void*, const wchar_t*, int, int, const MethodInfo*)>(getAbsoluteAddress(targetLibName, offset));
	return true;
}

static bool AssignCreateStringUTF8(std::string addrStr) {
	if (addrStr.empty())
		return false;
    int offset = stoul(addrStr, nullptr, 16);
	if (offset == 0)
		return false;
    System_String__CreateString_utf8 = reinterpret_cast<System_String_o * (*)(void*, const char*, int, int, const MethodInfo*)>(getAbsoluteAddress(targetLibName, offset));
	return true;
}

static void ShowToastOnUIThread(JNIEnv* env, jstring content, int duration)
{
	jmethodID showToastOnUIThread = env->GetStaticMethodID(utilsClass, "ShowToastOnUIThread", "(Ljava/lang/String;I)V");
	env->CallStaticVoidMethod(utilsClass, showToastOnUIThread, content, duration);
}

static void ShowToastOnUIThread(const char* content, int duration)
{
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        return;
	jstring jstr = env->NewStringUTF(content);
	ShowToastOnUIThread(env, jstr, duration);
	jvm->DetachCurrentThread();
}

static void ShowToastOnUIThread(std::string content, int duration)
{
	ShowToastOnUIThread(content.c_str(), duration);
}

static std::string GetStringValue(const char* key) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return "";
	jmethodID jKeyMethod = env->GetStaticMethodID(stringsClass, key, "()Ljava/lang/String;");
	jstring jValue = (jstring)env->CallStaticObjectMethod(stringsClass, jKeyMethod);
	std::string ret = ToStdString(env, jValue);
	jvm->DetachCurrentThread();
	return ret;
}

static void ChangeFeatureInt(const char* featureID, int featureNum, int value) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return;
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureInt = env->GetStaticMethodID(preferencesClass, "changeFeatureInt", "(Ljava/lang/String;II)V");
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureInt, jFeatureID, featureNum, value);
	jvm->DetachCurrentThread();
}

static void ChangeFeatureLong(const char* featureID, int featureNum, long value) {
    JNIEnv* env;
    if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        return;
    jstring jFeatureID = env->NewStringUTF(featureID);
    jmethodID jChangeFeatureInt = env->GetStaticMethodID(preferencesClass, "changeFeatureLong", "(Ljava/lang/String;IJ)V");
    env->CallStaticVoidMethod(preferencesClass, jChangeFeatureInt, jFeatureID, featureNum, value);
    jvm->DetachCurrentThread();
}

static void ChangeFeatureString(const char* featureID, int featureNum, const char* value) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return;
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureString = env->GetStaticMethodID(preferencesClass, "changeFeatureString", "(Ljava/lang/String;ILjava/lang/String;)V");
	jstring jValue = env->NewStringUTF(value);
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureString, jFeatureID, featureNum, jValue);
	jvm->DetachCurrentThread();
}

static void ChangeFeatureBool(const char* featureID, int featureNum, bool value) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return;
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureBool = env->GetStaticMethodID(preferencesClass, "changeFeatureBool", "(Ljava/lang/String;IZ)V");
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureBool, jFeatureID, featureNum, value);
	jvm->DetachCurrentThread();
}

static int ReadFeatureInt(int featureNum) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return 0;
	jmethodID jReadFeatureInt = env->GetStaticMethodID(preferencesClass, "readFeatureInt", "(I)I");
	int ret = env->CallStaticIntMethod(preferencesClass, jReadFeatureInt, featureNum);
	jvm->DetachCurrentThread();
	return ret;
}

static long ReadFeatureLong(int featureNum) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return 0;
	jmethodID jReadFeatureLong = env->GetStaticMethodID(preferencesClass, "readFeatureLong", "(I)J");
	long ret = env->CallStaticLongMethod(preferencesClass, jReadFeatureLong, featureNum);
	jvm->DetachCurrentThread();
	return ret;
}

static std::string ReadFeatureString(int featureNum) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return "";
	jmethodID jReadFeatureString = env->GetStaticMethodID(preferencesClass, "readFeatureString", "(I)Ljava/lang/String;");
	jstring ret = (jstring)env->CallStaticObjectMethod(preferencesClass, jReadFeatureString, featureNum);
	return ToStdString(env, ret);
}

static bool ReadFeatureBool(int featureNum) {
	JNIEnv* env;
	if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
		return false;
	jmethodID jReadFeatureBool = env->GetStaticMethodID(preferencesClass, "readFeatureBool", "(I)Z");
	bool ret = env->CallStaticBooleanMethod(preferencesClass, jReadFeatureBool, featureNum);
	jvm->DetachCurrentThread();
	return ret;
}

static void InitClasses(JNIEnv* env) {
    env->GetJavaVM(&jvm);
    jclass clasz = env->FindClass("com/ehvn/nroipchanger/Utils");
    utilsClass = (jclass)env->NewGlobalRef(clasz);
	clasz = env->FindClass("com/ehvn/nroipchanger/Preferences");
	preferencesClass = (jclass)env->NewGlobalRef(clasz);
	clasz = env->FindClass("com/ehvn/nroipchanger/Strings");
	stringsClass = (jclass)env->NewGlobalRef(clasz);
}

static jstring GetPackageName(JNIEnv* env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getPackageName = env->GetMethodID(activityClass, "getPackageName", "()Ljava/lang/String;");
    jstring packageName = (jstring)env->CallObjectMethod(activity, getPackageName);
    return packageName;
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

static System_String_o* CreateNetString(const wchar_t* str)    //string.CreateString(char* value, int startIndex, int length)
{
    auto* managed_str = static_cast<System_String_o*>(malloc(sizeof(System_String_o)));
    return System_String__CreateString_utf16(managed_str, str, 0, wcslen(str), nullptr);
}

static System_String_o* CreateNetString(const char* str)    //string.string CreateString(sbyte* value, int startIndex, int length)
{
    auto* managed_str = static_cast<System_String_o*>(malloc(sizeof(System_String_o)));
    return System_String__CreateString_utf8(managed_str, str, 0, strlen(str), nullptr);
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
