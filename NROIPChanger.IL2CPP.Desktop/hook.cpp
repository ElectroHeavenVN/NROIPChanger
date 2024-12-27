#include "AetherimMod/il2cpp_internals.h"
#include "AetherimMod/wrapper.hpp"
#include "hook.h"
#include "MinHookMod/mhook.h"
#include "utils.h"
#include "il2cpp.h"
#include <regex>

using namespace std;

#if defined(_WIN64)
#  define HOOKCCV __stdcall
#elif defined(_WIN32)
#  define HOOKCCV __cdecl
#endif

//[System]System.Net.Sockets.TcpClient::Connect(System.String,System.Int32)
//[System]System.Net.Sockets.TcpClient::.ctor(System.String,System.Int32)

wstring ipParameters = L"";
HWND mainWindowHandle;
LPWSTR originalWindowText;

static Il2CppMethodPointer System_Net_Sockets_TcpClient__Connect_address;
static Il2CppMethodPointer System_Net_Sockets_TcpClient___ctor_address;

static void ChangeIP(System_String_o** hostname, int32_t *port)
{
    if (lstrcmpW(&(*hostname)->fields.m_firstChar, L"127.0.0.1") == 0 || lstrcmpiW(&(*hostname)->fields.m_firstChar, L"localhost") == 0)
    {
		logDebug("Localhost");
		return;
    }
    string s_hostname = GetStdStr(*hostname);
	wstring original = GetStdWStr(*hostname) + L":" + to_wstring(*port);
    regex privateIPPattern(R"((^10\.)|(^172\.(1[6-9]|2[0-9]|3[0-1])\.)|(^192\.168\.))");
    if (regex_match(s_hostname, privateIPPattern) || ipParameters.empty()) {
        logDebugStd(original);
        return;
    }
    wstring ip_s = ipParameters.substr(0, ipParameters.find(L":"));
    wstring port_s = ipParameters.substr(ipParameters.find(L":") + 1);
	SetWindowTextW(mainWindowHandle, (wstring(originalWindowText) + L" [" + ipParameters + L"] - github.com/ElectroHeavenVN/NROIPChanger").c_str());
	*hostname = CreateNetString(ip_s);
    *port = stoi(port_s);
    logDebugStd(original + L" => " + ipParameters);
}

#pragma region Hooks
void (HOOKCCV* System_Net_Sockets_TcpClient__Connect_original)(System_Net_Sockets_TcpClient_o* _this, System_String_o* hostname, int32_t port, const MethodInfo* method);
void HOOKCCV System_Net_Sockets_TcpClient__Connect_hook(System_Net_Sockets_TcpClient_o* _this, System_String_o* hostname, int32_t port, const MethodInfo* method)
{
	ChangeIP(&hostname, &port);
    System_Net_Sockets_TcpClient__Connect_original(_this, hostname, port, method);
}
#pragma endregion

void SetupHooks()
{
	MH_Initialize();
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
    
    if (MH_OK != MH_CreateHook(reinterpret_cast<LPVOID*>(System_Net_Sockets_TcpClient__Connect_address), &System_Net_Sockets_TcpClient__Connect_hook, (LPVOID*)&System_Net_Sockets_TcpClient__Connect_original))
        logDebug("Hook System.Net.Sockets.TcpClient::Connect(string hostname, int port) failed!");
    else
        logDebug("Hooked System.Net.Sockets.TcpClient::Connect(string hostname, int port) successfully!");

    if (MH_OK != MH_EnableHook(MH_ALL_HOOKS))
        logDebug("Enable hooks failed!");
    else
        logDebug("Successfully enabled hooks!");

    originalWindowText = new WCHAR[256];
    GetWindowTextW(mainWindowHandle, originalWindowText, 256);
    SetWindowTextW(mainWindowHandle, (wstring(originalWindowText) + L" - github.com/ElectroHeavenVN/NROIPChanger").c_str());
}