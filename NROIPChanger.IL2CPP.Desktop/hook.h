#pragma once
#ifndef HOOK_H
#define HOOK_H
#include <string>

extern std::wstring ipParameters;
extern HWND mainWindowHandle;
extern bool forceRedirectLocalhost;
void SetupHooks();

#endif