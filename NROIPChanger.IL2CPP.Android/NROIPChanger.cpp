#include "AetherimMod/api.hpp"
#include "AetherimMod/wrapper.hpp"
#include "EHVNUtils.h"
#include "Includes/Logger.h"
#include "jni.h"
#include "Menu/Jni.hpp"
#include "Menu/Menu.hpp"
#include "Menu/Setup.hpp"
#include "NROIPChanger.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <errno.h>
#include <regex>
#include <sstream>
#include <string>
#include <sys/resource.h>
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

static bool enabled = false;
static bool showNotification = false;
static string customIP = "";
static int customPort = -1;
static bool warningShown = false;
static string lastToast = "";
static long lastTimeShowToast = 0;

Il2CppMethodPointer System_Net_Sockets_TcpClient__Connect_address = 0;

jobjectArray GetFeatureList(JNIEnv* env, jobject context) {
	jobjectArray ret;
	vector<string> features = {
		"1_Toggle_activate",
		"2_Toggle_showNoti_True",
		"3_InputText_newIPAddr",
		"4_InputValue_newPort",
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
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	long currentTime = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
	if ((lastToast == content && currentTime - lastTimeShowToast <= 2000) && !forceShow)
		return;
	ShowToastOnUIThread(content, duration);
	lastToast = content;
	lastTimeShowToast = currentTime;
}

static void ShowToast(string content, int duration, bool forceShow = false)
{
	ShowToast((char*)content.c_str(), duration, forceShow);
}

static void ShowPirateServerWarning()
{ 
	if (warningShown)
		return;
	string str = GetStringValue("pirateServerWarning");
	if (str != "Protect yourself from being scammed when playing on pirate servers!" && str != utf8::utf16to8(std::u16string(u"Đừng để bị lùa như 1 con gà khi chơi server lậu!")))
		str = "Protect yourself from being scammed when playing on pirate servers!";
	ShowToast(str, ToastLength::LENGTH_LONG, true);
	warningShown = true;
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
	if (!enabled || customIP.empty() || customPort < 0 || regex_match(s_hostname, privateIPPattern))
	{
		ShowToast(originalIPAddr, ToastLength::LENGTH_SHORT);
		return false;
	}
	regex teaMobiIPPattern(R"(dragon[\w]*\.(teamobi|indonaga)\.com)");
	if (!regex_match(customIP, teaMobiIPPattern))
		ShowPirateServerWarning();
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
		//Found a way to hook functions without khowing its address! So there's no need to set the addresses here!
	}
}

static void InstallHooks()
{
	Il2cpp::initialize();
	const auto il2cppImages = std::make_unique<Wrapper>();
	const auto system = il2cppImages->get_image("System.dll");
	Class* tcpClient = system->get_class("TcpClient", "System.Net.Sockets");
	void* iter = NULL;
	while (Method* method = tcpClient->get_methods(&iter))
	{
		if (!strcmp("Connect", method->get_name()) && method->get_param_count() == 2 && !strcmp(method->get_param_name(0), "hostname")) {
			System_Net_Sockets_TcpClient__Connect_address = method->methodPointer;
			break;
		}
	}
	HOOK_BY_NAME(System_Net_Sockets_TcpClient__Connect);
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
	//count = 0;
	//while (!isLibraryLoaded("libEHVNUtils.so")) {
	//	sleep(1);
	//	count++;
	//	if (count > 15) {
	//		exit(0);
	//		return nullptr;
	//	}
	//}
	InstallHooks();
	LOGI("Initialization complete.");
	return nullptr;
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
		if (ReadFeatureString(3).empty()) {
			ChangeFeatureString("newIPAddr", 3, str.substr(0, str.find(':')).c_str());
			ChangeFeatureInt("newPort", 4, stoi(str.substr(str.find(':') + 1)));
			ShowToast(GetStringValue("defaultIPAddress") + ": " + str, ToastLength::LENGTH_SHORT, true);
		}
		break;
	}
	delete buffer;
	AAsset_close(asset);
}

//context only available after the menu is initialized, so we need to load the resources in the Init function
static void LoadResources(JNIEnv* env, jobject thiz, jobject ctx, jobject title, jobject subtitle)
{
	InitMenu(env, thiz, ctx, title, subtitle);
	LoadCustomIPFromResource(env, ctx);
}

extern "C" JNIEXPORT void JNICALL Java_com_ehvn_nroipchanger_Main_Init(JNIEnv* env, jclass clazz, jobject ctx) {
	InitClasses(env);
	LOGI("Package name: %s", ToStdString(env, GetPackageName(env, ctx)).c_str());
	if (strcmp(ENV_VERSION, "nightly") == 0)
		ShowToast("NROIPChanger Nightly (" ABI ")\n" REPO, ToastLength::LENGTH_LONG);
	else
		ShowToast("NROIPChanger v" ENV_VERSION " (" ABI ")\n" REPO, ToastLength::LENGTH_LONG);
	string str = GetStringValue("installFromOtherSourcesWarning");
    if (str != "Do not install from other sources!" && str != utf8::utf16to8(std::u16string(u"Không cài từ các nguồn không rõ!")))
		str = "Do not install from other sources!";
	ShowToast(str, ToastLength::LENGTH_SHORT);
	pthread_t ptid;
	pthread_create(&ptid, nullptr, Initialize, nullptr);
	JNINativeMethod methods[] = {
		{"Init", "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", reinterpret_cast<void*>(LoadResources)},
	};
	env->RegisterNatives(env->FindClass("com/ehvn/nroipchanger/Menu"), methods, 1);
}