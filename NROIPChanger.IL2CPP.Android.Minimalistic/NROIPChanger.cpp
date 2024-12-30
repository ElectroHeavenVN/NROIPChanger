#include "EHVNUtils.h"
#include "Includes/Logger.h"
#include "jni.h"
#include "NROIPChanger.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <errno.h>
#include <regex>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

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
	const char * NROIPChanger::getPlatformABI()
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

static string customIP;
static JavaVM* jvm;
static jclass mainClass;

static void ShowToast(char* content, int duration)
{
    LOGI("ShowToast: %s", content);
    ShowToastOnUIThread(jvm, mainClass, content, duration);
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
	if (regex_match(s_hostname, privateIPPattern) || customIP.empty())
    {
        ShowToast(originalIPAddr, ToastLength::LENGTH_SHORT);
        return false;
    }
    string ip_s = customIP.substr(0, customIP.find(":"));
    string port_s = customIP.substr(customIP.find(":") + 1);
    string newIPAddr = ip_s + ":" + port_s;
    System_String_o* newHostname = CreateNetString(ip_s);
    int newPort = stoi(port_s);
    ShowToast(originalIPAddr + " -> " + newIPAddr, ToastLength::LENGTH_SHORT);
	original(_this, newHostname, newPort, nullptr);
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

static void InstallHooks()
{
	if (!InstallCreateStrings())
        ShowToast("wrong String.CreateString addresses!", ToastLength::LENGTH_SHORT);
    HOOK_BY_NAME(System_Net_Sockets_TcpClient__Connect);
    else 
        ShowToast("Failed to install hooks.", ToastLength::LENGTH_SHORT);
}

static void* Initialize(void*) {
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
    InstallHooks();
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
    while (getline(ss, hookAddr, '|')) {
        DWORD addr = stoul(hookAddr, nullptr, 16);
        hookAddresses.push_back(addr);
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
        customIP = str;
        LOGI("Custom IP server: %s", str.c_str());
        break;
    }
    delete buffer;
    AAsset_close(asset);
}

void Init(JNIEnv* env, jobject ctx)
{
	env->GetJavaVM(&jvm);
    LOGI("Package name: %s", ToStdString(env, GetPackageName(env, ctx)).c_str());
	if (strcmp(ENV_VERSION, "nightly") == 0)
        ShowToast("NROIPChanger Nightly (" ABI ") by ElectroHeavenVN", ToastLength::LENGTH_LONG);
    else
        ShowToast("NROIPChanger v" ENV_VERSION " (" ABI ") by ElectroHeavenVN", ToastLength::LENGTH_LONG);
    ShowToast("NROIPChanger v" ENV_VERSION " (" ABI ") by ElectroHeavenVN", ToastLength::LENGTH_LONG);
    ShowToast("https://github.com/ElectroHeavenVN/NROIPChanger", ToastLength::LENGTH_LONG);
    ShowToast("Do not install from other sources!", ToastLength::LENGTH_SHORT);
    LoadHookAddressesFromResource(env, ctx);
    LoadCustomIPFromResource(env, ctx);
    pthread_t ptid;
    pthread_create(&ptid, nullptr, Initialize, nullptr);
}

extern "C" JNIEXPORT void JNICALL Java_com_ehvn_nroipchanger_Main_Init(JNIEnv* env, jclass clazz, jobject ctx) {
    mainClass = (jclass)env->NewGlobalRef(clazz);
	Init(env, ctx);
}