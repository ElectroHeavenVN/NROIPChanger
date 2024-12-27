#include <windows.h>
#include <string>
#include "AetherimMod/wrapper.hpp"
#include "AetherimMod/il2cpp_internals.h"
#include "il2cpp.h"

bool debugMode = false;

std::string utf16_to_utf8(const wchar_t* utf16String, size_t length)
{
    if (length == -1)
        length = lstrlenW(utf16String);
    std::string retStr;
    int sizeRequired = WideCharToMultiByte(CP_UTF8, 0, utf16String, -1, NULL, 0, NULL, NULL);
    if (sizeRequired > 0)
    {
        std::vector<char> utf8String(sizeRequired);
        int bytesConverted = WideCharToMultiByte(CP_UTF8, 0, utf16String, -1, &utf8String[0], utf8String.size(), NULL, NULL);
        if (bytesConverted != 0)
            retStr = &utf8String[0];
    }
    return retStr;
}

wchar_t* ConvertCharToWchar(const char* charString)
{
    size_t length = mbstowcs(NULL, charString, 0);
    if (length == static_cast<size_t>(-1))
        return nullptr;
    wchar_t* wcharString = new wchar_t[length + 1];
    size_t convertedLength = mbstowcs(wcharString, charString, length);
    if (convertedLength == static_cast<size_t>(-1))
    {
        delete[] wcharString;
        return nullptr;
    }
    wcharString[length] = L'\0';
    return wcharString;
}

System_String_o* CreateNetString(const char* str)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf8(str));
}

System_String_o* CreateNetString(const wchar_t* str)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf16(str, wcslen(str)));
}

System_String_o* CreateNetString(const char* str, uint32_t len)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf8_with_length(str, len));
}

System_String_o* CreateNetString(std::wstring str)
{
    return reinterpret_cast<System_String_o*>(Il2cpp::create_string_utf16(str.c_str(), str.length()));
}

std::wstring GetStdWStr(System_String_o* str)
{
    return std::wstring(&str->fields.m_firstChar, &str->fields.m_firstChar + str->fields.m_stringLength);
}

std::string GetStdStr(System_String_o* str)
{
    return utf16_to_utf8(&str->fields.m_firstChar, str->fields.m_stringLength);
}

void logDebug(const char* format...)
{
    if (!debugMode)
        return;
    printf(format);
    printf("\r\n");
}

void logDebug(const wchar_t* format...)
{
    if (!debugMode)
        return;
    wprintf(format);
    printf("\r\n");
}

void logDebugStd(std::string str)
{
    logDebug(str.c_str());
}

void logDebugStd(std::wstring str)
{
    logDebug(str.c_str());
}

void logDebug(System_String_o* str)
{
    logDebug(&str->fields.m_firstChar);
}

struct handle_data {
    unsigned long process_id;
    HWND window_handle;
};

BOOL isMainWindow(HWND handle)
{
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
    handle_data& data = *(handle_data*)lParam;
    unsigned long process_id = 0;
    GetWindowThreadProcessId(handle, &process_id);
    if (data.process_id != process_id || !isMainWindow(handle))
        return TRUE;
    data.window_handle = handle;
    return FALSE;
}

HWND findMainWindow(unsigned long process_id)
{
    handle_data data;
    data.process_id = process_id;
    data.window_handle = 0;
    EnumWindows(enum_windows_callback, (LPARAM)&data);
    return data.window_handle;
}

bool isMainWindowVisible(unsigned long pid, HWND& hWnd) {
    hWnd = findMainWindow(pid);
    return hWnd != NULL;
}