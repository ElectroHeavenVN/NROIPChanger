// dllmain.cpp : Defines the entry point for the DLL application.
#include "MinHookMod/mhook.h"
#include <shellapi.h>
#include "utils.h"
#include "hook.h"
#include <string>

static void Main()
{
    HWND hWnd;
    while (!isMainWindowVisible(GetCurrentProcessId(), hWnd))
        Sleep(50);
    mainWindowHandle = hWnd;
    SetupHooks();
    HANDLE pipe = {};
    Sleep(1000);
    std::wstring serverPipeName = (L"\\\\.\\pipe\\NROIPChanger.IL2CPP.Desktop+" + std::to_wstring(GetCurrentProcessId()));
    if (WaitNamedPipe(serverPipeName.c_str(), NMPWAIT_WAIT_FOREVER))
    {
        do {
            pipe = CreateFile(serverPipeName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
            Sleep(100);
        } while (!pipe || pipe == INVALID_HANDLE_VALUE);
    }
    DWORD bytesRead;
    int len = 0;
    if (!pipe || pipe == INVALID_HANDLE_VALUE)
        return;
    if (ReadFile(pipe, &len, sizeof(len), &bytesRead, NULL) && bytesRead == sizeof(int))
    {
        wchar_t* buffer = new wchar_t[len];
        if (ReadFile(pipe, buffer, len * sizeof(wchar_t), &bytesRead, NULL))
            ipParameters = std::wstring(buffer, len);
        delete[] buffer;
        bool debug = false;
        if (ReadFile(pipe, &debug, sizeof(debug), &bytesRead, NULL) && bytesRead == sizeof(bool))
            debugMode = debug;
		if (ReadFile(pipe, &forceRedirectLocalhost, sizeof(forceRedirectLocalhost), &bytesRead, NULL) && bytesRead == sizeof(bool))
			logDebug("Force redirect localhost: %s", forceRedirectLocalhost ? "true" : "false");
    }
    CloseHandle(pipe);
    if (debugMode)
    {
        AllocConsole();
        if (strcmp(VERSION, "nightly") == 0)
		    SetConsoleTitle(L"NROIPChanger Nightly - debug console");
        else 
			SetConsoleTitle(L"NROIPChanger v" VERSION " - debug console");
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        logDebug("Debug mode enabled! Log messages will be displayed here.");
        logDebug("Don't close this window, it will close the game.");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        MH_Uninitialize();
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}