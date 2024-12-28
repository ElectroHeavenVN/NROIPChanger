#pragma once
#ifndef IL2CPP_H
#define IL2CPP_H
#include <cstdint>
#include "il2cpp_internals.h"

struct System_String_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_CompareTo;
    VirtualInvokeData _5_Clone;
    VirtualInvokeData _6_GetTypeCode;
    VirtualInvokeData _7_System_IConvertible_ToBoolean;
    VirtualInvokeData _8_System_IConvertible_ToChar;
    VirtualInvokeData _9_System_IConvertible_ToSByte;
    VirtualInvokeData _10_System_IConvertible_ToByte;
    VirtualInvokeData _11_System_IConvertible_ToInt16;
    VirtualInvokeData _12_System_IConvertible_ToUInt16;
    VirtualInvokeData _13_System_IConvertible_ToInt32;
    VirtualInvokeData _14_System_IConvertible_ToUInt32;
    VirtualInvokeData _15_System_IConvertible_ToInt64;
    VirtualInvokeData _16_System_IConvertible_ToUInt64;
    VirtualInvokeData _17_System_IConvertible_ToSingle;
    VirtualInvokeData _18_System_IConvertible_ToDouble;
    VirtualInvokeData _19_System_IConvertible_ToDecimal;
    VirtualInvokeData _20_System_IConvertible_ToDateTime;
    VirtualInvokeData _21_ToString;
    VirtualInvokeData _22_System_IConvertible_ToType;
    VirtualInvokeData _23_System_Collections_IEnumerable_GetEnumerator;
    VirtualInvokeData _24_CompareTo;
    VirtualInvokeData _25_System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
    VirtualInvokeData _26_Equals;
};
struct System_String_c {
    Il2CppClass_1 _1;
    struct System_String_StaticFields* static_fields;
    void* rgctx_data;
    Il2CppClass_2 _2;
    System_String_VTable vtable;
};
struct System_String_StaticFields {
    struct System_String_o* Empty;
};
struct System_String_Fields {
    int32_t m_stringLength;
    wchar_t m_firstChar;
};
struct System_String_o {
    System_String_c* klass;
    void* monitor;
    System_String_Fields fields;
};

struct System_Net_Sockets_TcpClient_Fields {
    void* m_ClientSocket;
    bool m_Active;
    void* m_DataStream;
    int32_t m_Family;
    bool m_CleanedUp;
};
struct System_Net_Sockets_TcpClient_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Dispose;
    VirtualInvokeData _5_Dispose;
};
struct System_Net_Sockets_TcpClient_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Net_Sockets_TcpClient_VTable vtable;
};
struct System_Net_Sockets_TcpClient_o {
    System_Net_Sockets_TcpClient_c* klass;
    void* monitor;
    System_Net_Sockets_TcpClient_Fields fields;
};
#endif