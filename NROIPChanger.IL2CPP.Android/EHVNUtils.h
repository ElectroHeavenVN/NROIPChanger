#pragma once
#ifndef EHVNUTILS_H
#define EHVNUTILS_H

#include "AetherimMod/api.hpp"
#include "IL2CPP/il2cpp.h"
#include "Includes/Logger.h"
#include "Includes/Macros.h"
#include "Includes/Utils.hpp"
#include "utfcpp/utf8.h"
#include <jni.h>

#define HOOK_BY_NAME(n) if (n##_address != 0) HOOK_ADDR(reinterpret_cast<DWORD>(n##_address), n##_hook, n##_original)

static JavaVM* jvm;
static jclass preferencesClass;
static jclass utilsClass;
static jclass stringsClass;

static std::string ToStdString(JNIEnv * env, jstring jStr);

static void ShowToastOnUIThread(JNIEnv* env, jstring content, int duration)
{
	jmethodID showToastOnUIThread = env->GetStaticMethodID(utilsClass, "ShowToastOnUIThread", "(Ljava/lang/String;I)V");
	env->CallStaticVoidMethod(utilsClass, showToastOnUIThread, content, duration);
}

static void ShowToastOnUIThread(const char* content, int duration)
{
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return;
		needDetach = true;
	}
	jstring jstr = env->NewStringUTF(content);
	ShowToastOnUIThread(env, jstr, duration);
	if (needDetach)
		jvm->DetachCurrentThread();
}

static void ShowToastOnUIThread(std::string content, int duration)
{
	ShowToastOnUIThread(content.c_str(), duration);
}

static std::string GetStringValue(const char* key) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return key;
		needDetach = true;
	}
	jmethodID jKeyMethod = env->GetStaticMethodID(stringsClass, key, "()Ljava/lang/String;");
	if (!jKeyMethod)
		return key;
	jstring jValue = (jstring)env->CallStaticObjectMethod(stringsClass, jKeyMethod);
	std::string ret = ToStdString(env, jValue);
	if (needDetach)
		jvm->DetachCurrentThread();
	return ret;
}

static void ChangeFeatureInt(const char* featureID, int featureNum, int value) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return;
		needDetach = true;
	}
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureInt = env->GetStaticMethodID(preferencesClass, "changeFeatureInt", "(Ljava/lang/String;II)V");
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureInt, jFeatureID, featureNum, value);
	if (needDetach)
		jvm->DetachCurrentThread();
}

static void ChangeFeatureLong(const char* featureID, int featureNum, long value) {
    JNIEnv* env;
    if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        return;
    jstring jFeatureID = env->NewStringUTF(featureID);
    jmethodID jChangeFeatureInt = env->GetStaticMethodID(preferencesClass, "changeFeatureLong", "(Ljava/lang/String;IJ)V");
    env->CallStaticVoidMethod(preferencesClass, jChangeFeatureInt, jFeatureID, featureNum, value);
    //jvm->DetachCurrentThread();
}

static void ChangeFeatureString(const char* featureID, int featureNum, const char* value) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return;
		needDetach = true;
	}
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureString = env->GetStaticMethodID(preferencesClass, "changeFeatureString", "(Ljava/lang/String;ILjava/lang/String;)V");
	jstring jValue = env->NewStringUTF(value);
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureString, jFeatureID, featureNum, jValue);
	if (needDetach)
		jvm->DetachCurrentThread();
}

static void ChangeFeatureBool(const char* featureID, int featureNum, bool value) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return;
		needDetach = true;
	}
	jstring jFeatureID = env->NewStringUTF(featureID);
	jmethodID jChangeFeatureBool = env->GetStaticMethodID(preferencesClass, "changeFeatureBool", "(Ljava/lang/String;IZ)V");
	env->CallStaticVoidMethod(preferencesClass, jChangeFeatureBool, jFeatureID, featureNum, value);
	if (needDetach)
		jvm->DetachCurrentThread();
}

static int ReadFeatureInt(int featureNum) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return 0;
		needDetach = true;
	}
	jmethodID jReadFeatureInt = env->GetStaticMethodID(preferencesClass, "readFeatureInt", "(I)I");
	int ret = env->CallStaticIntMethod(preferencesClass, jReadFeatureInt, featureNum);
	if (needDetach)
		jvm->DetachCurrentThread();
	return ret;
}

static long ReadFeatureLong(int featureNum) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return 0L;
		needDetach = true;
	}
	jmethodID jReadFeatureLong = env->GetStaticMethodID(preferencesClass, "readFeatureLong", "(I)J");
	long ret = env->CallStaticLongMethod(preferencesClass, jReadFeatureLong, featureNum);
	if (needDetach)
		jvm->DetachCurrentThread();
	return ret;
}

static std::string ReadFeatureString(int featureNum) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return "";
		needDetach = true;
	}
	jmethodID jReadFeatureString = env->GetStaticMethodID(preferencesClass, "readFeatureString", "(I)Ljava/lang/String;");
	jstring ret = (jstring)env->CallStaticObjectMethod(preferencesClass, jReadFeatureString, featureNum);
	std::string str = ToStdString(env, ret);
	if (needDetach)
		jvm->DetachCurrentThread();
	return str;
}

static bool ReadFeatureBool(int featureNum) {
	JNIEnv* env;
	bool needDetach = false;
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
			return false;
		needDetach = true;
	}
	jmethodID jReadFeatureBool = env->GetStaticMethodID(preferencesClass, "readFeatureBool", "(I)Z");
	bool ret = env->CallStaticBooleanMethod(preferencesClass, jReadFeatureBool, featureNum);
	if (needDetach)
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
