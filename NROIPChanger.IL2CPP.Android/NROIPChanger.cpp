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

static jclass utilsClass;
static JavaVM* jvm;
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
		"2_Toggle_showNoti",
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
	ShowToastOnUIThread(jvm, utilsClass, content, duration);
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

void Changes(JNIEnv* env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jlong Lvalue, jboolean boolean, jstring text) {
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
	if (strcmp(ENV_VERSION, "nightly") == 0)
		ShowToast("NROIPChanger Nightly (" ABI ")\n" REPO, ToastLength::LENGTH_LONG, true);
	else
		ShowToast("NROIPChanger v" ENV_VERSION " (" ABI ")\n" REPO, ToastLength::LENGTH_LONG, true);
	ShowToast("Do not install from other sources!", ToastLength::LENGTH_SHORT, true);
	return nullptr;
}

__attribute__((constructor)) void lib_main()
{
	pthread_t ptid;
	pthread_create(&ptid, NULL, Initialize, NULL);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv* env;
	vm->GetEnv((void**)&env, JNI_VERSION_1_6);
	env->GetJavaVM(&jvm);
	jclass clasz = env->FindClass("com/ehvn/nroipchanger/Utils");
	utilsClass = (jclass)env->NewGlobalRef(clasz);
	return JNIOnLoad(vm, reserved);
}