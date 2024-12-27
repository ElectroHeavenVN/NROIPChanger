#pragma once
#ifndef UTILS_H
#define UTILS_H
#include <windows.h>
#include <string>
#include "AetherimMod/wrapper.hpp"
#include "AetherimMod/il2cpp_internals.h"
#include "il2cpp.h"

extern bool debugMode;
std::string utf16_to_utf8(const wchar_t* utf16String, size_t length);
wchar_t* ConvertCharToWchar(const char* charString);
System_String_o* CreateNetString(const char* str);
System_String_o* CreateNetString(const wchar_t* str);
System_String_o* CreateNetString(const char* str, uint32_t len);
System_String_o* CreateNetString(std::wstring str);
std::wstring GetStdWStr(System_String_o* str);
std::string GetStdStr(System_String_o* str);
void logDebug(const char* format...);
void logDebug(const wchar_t* format...);
void logDebugStd(std::string str);
void logDebugStd(std::wstring str);
void logDebug(System_String_o* str);
BOOL isMainWindow(HWND handle);
HWND findMainWindow(unsigned long process_id);
bool isMainWindowVisible(unsigned long pid, HWND& hWnd);
#endif // !UTILS_H
