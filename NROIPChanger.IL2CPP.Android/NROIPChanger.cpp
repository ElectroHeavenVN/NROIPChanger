#include "EHVNUtils.h"
#include "IL2CPP/il2cpp.h"
#include "Includes/Logger.h"
#include "Includes/Macros.h"
#include "Includes/Utils.hpp"
#include "jni.h"
#include "Menu/Jni.hpp"
#include "Menu/Menu.hpp"
#include "Menu/Setup.hpp"
#include "NROIPChanger.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <cstring>
#include <dlfcn.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <list>
#include <locale>
#include <pthread.h>
#include <regex>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/resource.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

#if defined(__arm__)
#define ABI "armeabi-v7a"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#else
#define ABI "unknown"
#endif

extern "C" {
	/* This trivial function returns the platform ABI for which this dynamic native library is compiled.*/
	const char* NROIPChanger::getPlatformABI()
	{
		LOGI("This dynamic shared library is compiled with ABI: %s", ABI);
		return "This native library is compiled with ABI: " ABI ".";
	}

	void NROIPChanger()
	{
	}

	NROIPChanger::NROIPChanger()
	{
	}

	NROIPChanger::~NROIPChanger()
	{
	}
}

//#if defined(__aarch64__)
//#define HOOKCCV __fastcall
//#elif defined(__arm__)
//#define HOOKCCV __fastcall
//#endif
#define HOOKCCV
#define targetLibName "libil2cpp.so"
#define REPO "https://github.com/ElectroHeavenVN/NROIPChanger"

static bool hooked = false;
static bool hasCreateStringUTF8 = false;
static bool hasCreateStringUTF16 = false;

static bool enabled = false;
static bool showNotification = false;
static string customIP = "";
static int customPort = -1;

DWORD System_Net_Sockets_TcpClient__Connect_address = 0;

jobjectArray GetFeatureList(JNIEnv* env, jobject context) {
	jobjectArray ret;
	vector<string> features = {
		"1_Toggle_activate",
		"2_Toggle_showNoti_True",
		"3_InputText_newIPAddr",
		"4_InputValue_newPort",
		"Collapse_hookAddr",
		"CollapseAdd_Category_hookAddrNotice",
		"5_CollapseAdd_InputText_utf8CreateStringRVA",
		"6_CollapseAdd_InputText_utf16CreateStringRVA",
		"7_CollapseAdd_InputText_tcpClientConnectRVA",
	};
	int Total_Feature = features.size();
	ret = (jobjectArray)env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	for (int i = 0; i < Total_Feature; i++)
		env->SetObjectArrayElement(ret, i, env->NewStringUTF(features.at(i).c_str()));
	return (ret);
}

static void ShowToast(char* content, int duration, bool forceShow = false)
{
	LOGI("ShowToast: %s", content);
	if (!forceShow && !showNotification)
		return;
	ShowToastOnUIThread(content, duration);
}

static void ShowToast(string content, int duration)
{
	ShowToast((char*)content.c_str(), duration);
}

static bool ChangeIP(System_Net_Sockets_TcpClient_o* _this, System_String_o* hostname, int32_t port, void (HOOKCCV* original)(System_Net_Sockets_TcpClient_o*, System_String_o*, int32_t, const MethodInfo*))
{
	if (Equals(hostname, L"127.0.0.1") || Equals(hostname, L"localhost"))
	{
		ShowToast("Localhost", ToastLength::LENGTH_SHORT);
		return false;
	}
	string s_hostname = GetStdStr(hostname);
	string originalIPAddr = s_hostname + ":" + to_string(port);
	regex privateIPPattern(R"((^10\.)|(^172\.(1[6-9]|2[0-9]|3[0-1])\.)|(^192\.168\.))");
	if (!enabled || customIP.empty() || customPort < 0 || !hasCreateStringUTF8 || !hasCreateStringUTF16 || regex_match(s_hostname, privateIPPattern))
	{
		ShowToast(originalIPAddr, ToastLength::LENGTH_SHORT);
		return false;
	}
	string newIPAddr = customIP + ":" + to_string(customPort);
	System_String_o* newHostname = CreateNetString(customIP);
	ShowToast(originalIPAddr + " -> " + newIPAddr, ToastLength::LENGTH_SHORT);
	original(_this, newHostname, customPort, nullptr);
	return true;
}

#pragma region Hooks
void (HOOKCCV* System_Net_Sockets_TcpClient__Connect_original)(System_Net_Sockets_TcpClient_o* _this, System_String_o* hostname, int32_t port, const MethodInfo* method);
void HOOKCCV System_Net_Sockets_TcpClient__Connect_hook(System_Net_Sockets_TcpClient_o* _this, System_String_o* hostname, int32_t port, const MethodInfo* method)
{
	if (!ChangeIP(_this, hostname, port, System_Net_Sockets_TcpClient__Connect_original))
		System_Net_Sockets_TcpClient__Connect_original(_this, hostname, port, method);
}
#pragma endregion

void Changes(JNIEnv* env, jclass clazz, jobject obj, jint featNum, jstring featureID, jint value, jlong Lvalue, jboolean boolean, jstring text) {
	//LOGI("Changes: featNum: %d, value: %d, Lvalue: %lld, boolean: %d, text: %s", featNum, value, Lvalue, boolean, env->GetStringUTFChars(text, 0));
	switch (featNum) 
	{
		case 1: //  on/off
			enabled = boolean;
			break;
		case 2: //  enable/disable notification
			showNotification = boolean;
			break;
		case 3: //custom ip
			customIP = ToStdString(env, text);
			break;
		case 4: //custom port
			if (value > 0)
				customPort = value;
			break;
		case 5: //  System_String__CreateString_utf8 address
			if (AssignCreateStringUTF8(ToStdString(env, text)))
				hasCreateStringUTF8 = true;
			break;
		case 6: //  System_String__CreateString_utf16 address
			if (AssignCreateStringUTF16(ToStdString(env, text)))
				hasCreateStringUTF16 = true;
			break;
		case 7: //  System_Net_Sockets_TcpClient__Connect address
			if (hooked)
				break;
			string offset = ToStdString(env, text);
			if (offset.empty())
				break;
			System_Net_Sockets_TcpClient__Connect_address = stoul(offset, nullptr, 16);
			if (System_Net_Sockets_TcpClient__Connect_address == 0)
				break;
			HOOK_BY_NAME(System_Net_Sockets_TcpClient__Connect);
			hooked = true;
			break;
	}
}

static void* Initialize(void*)
{
	LOGI("Initializing...");
	do
		sleep(1);
	while (!isLibraryLoaded(targetLibName));
	int count = 0;
	while (!isLibraryLoaded("libNROIPChanger.so")) {
		sleep(1);
		count++;
		if (count > 15) {
			exit(0);
			return nullptr;
		}
	}
	//InstallHooks();	//Hooks will be installed from the Changes function
	LOGI("Initialization complete.");
	return nullptr;
}

static void LoadHookAddressesFromResource(JNIEnv* env, jobject ctx)
{
	jclass context = env->GetObjectClass(ctx);
	jmethodID getResources = env->GetMethodID(context, "getResources", "()Landroid/content/res/Resources;");
	jobject resourcesInstance = env->CallObjectMethod(ctx, getResources);
	jclass resources = env->GetObjectClass(resourcesInstance);
	jmethodID getAssets = env->GetMethodID(resources, "getAssets", "()Landroid/content/res/AssetManager;");
	jobject assetManager = env->CallObjectMethod(resourcesInstance, getAssets);
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	AAsset* asset = AAssetManager_open(mgr, "hook_addresses", AASSET_MODE_BUFFER);
	if (nullptr == asset)
		return;
	long size = AAsset_getLength(asset);
	char* buffer = (char*)malloc(sizeof(char) * size);
	AAsset_read(asset, buffer, size);
	stringstream ss(buffer);
	string hookAddr;
	for (int i = 0; getline(ss, hookAddr, '|'); i++) {
		if (i == 0) {
			if (ReadFeatureString(5).empty()) {
				ChangeFeatureString("utf8CreateStringRVA", 5, hookAddr.c_str());
				LOGI("Default utf8CreateStringRVA: %s", hookAddr.c_str());
			}
		}
		else if (i == 1) {
			if (ReadFeatureString(6).empty()) {
				ChangeFeatureString("utf16CreateStringRVA", 6, hookAddr.c_str());
				LOGI("Default utf16CreateStringRVA: %s", hookAddr.c_str());
			}
		}
		else if (i == 2) {
			if (ReadFeatureString(7).empty()) {
				ChangeFeatureString("tcpClientConnectRVA", 7, hookAddr.c_str());
				LOGI("Default tcpClientConnectRVA: %s", hookAddr.c_str());
			}
		}
		hookAddr = "";
	}
	delete buffer;
	AAsset_close(asset);
}

static void LoadCustomIPFromResource(JNIEnv* env, jobject ctx)
{
	jclass context = env->GetObjectClass(ctx);
	jmethodID getResources = env->GetMethodID(context, "getResources", "()Landroid/content/res/Resources;");
	jobject resourcesInstance = env->CallObjectMethod(ctx, getResources);
	jclass resources = env->GetObjectClass(resourcesInstance);
	jmethodID getAssets = env->GetMethodID(resources, "getAssets", "()Landroid/content/res/AssetManager;");
	jobject assetManager = env->CallObjectMethod(resourcesInstance, getAssets);
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	AAsset* asset = AAssetManager_open(mgr, "ip_server", AASSET_MODE_BUFFER);
	if (nullptr == asset)
		return;
	long size = AAsset_getLength(asset);
	if (0 == size)
		return;
	char* buffer = (char*)malloc(sizeof(char) * size);
	AAsset_read(asset, buffer, size);
	stringstream ss(buffer);
	string str;
	while (getline(ss, str)) {
		if (str.empty() || str.length() < 5 || str[0] == '#') {
			str = "";
			continue;
		}
		if (ReadFeatureString(3).empty())
			ChangeFeatureString("newIPAddr", 3, str.substr(0, str.find(':')).c_str());
		if (ReadFeatureInt(4) == 0)
			ChangeFeatureInt("newPort", 4, stoi(str.substr(str.find(':') + 1)));
		LOGI("Default custom IP server: %s", str.c_str());
		break;
	}
	delete buffer;
	AAsset_close(asset);
}

//context only available after the menu is initialized, so we need to load the resources in the Init function
static void LoadResources(JNIEnv* env, jobject thiz, jobject ctx, jobject title, jobject subtitle)
{
	InitMenu(env, thiz, ctx, title, subtitle);
	LoadHookAddressesFromResource(env, ctx);
	LoadCustomIPFromResource(env, ctx);
}

extern "C" JNIEXPORT void JNICALL Java_com_ehvn_nroipchanger_Main_Init(JNIEnv* env, jclass clazz, jobject ctx) {
	InitClasses(env);
	LOGI("Package name: %s", ToStdString(env, GetPackageName(env, ctx)).c_str());
	if (strcmp(ENV_VERSION, "nightly") == 0)
		ShowToast("NROIPChanger Nightly (" ABI ")\n" REPO, ToastLength::LENGTH_LONG);
	else
		ShowToast("NROIPChanger v" ENV_VERSION " (" ABI ")\n" REPO, ToastLength::LENGTH_LONG);
	ShowToast("Do not install from other sources!", ToastLength::LENGTH_SHORT);
	pthread_t ptid;
	pthread_create(&ptid, nullptr, Initialize, nullptr);
	JNINativeMethod methods[] = {
		{"Init", "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", reinterpret_cast<void*>(LoadResources)},
	};
	env->RegisterNatives(env->FindClass("com/ehvn/nroipchanger/Menu"), methods, 1);
}