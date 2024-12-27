//
// Created by EHVN on 04/12/2023.
//

#pragma once
#ifndef IL2CPP_H
#define IL2CPP_H
#include <cstdint>
#include "il2cpp_internals.h"

struct System_Int32_Fields {
    int32_t m_value;
};
struct System_Int32_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_CompareTo;
    VirtualInvokeData _5_ToString;
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
    VirtualInvokeData _23_CompareTo;
    VirtualInvokeData _24_Equals;
};
struct System_Int32_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Int32_VTable vtable;
};
struct System_Int32_o : Il2CppObject {
    System_Int32_Fields fields;
};

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

struct UnityEngine_Rect_Fields {
    float m_XMin;
    float m_YMin;
    float m_Width;
    float m_Height;
};
struct UnityEngine_Rect_o {
    UnityEngine_Rect_Fields fields;
};

struct System_String_array {
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    System_String_o* m_Items[65535];
};
struct System_Byte_array {
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    char m_Items[65535];
};
struct System_UInt16_array {
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    uint16_t m_Items[65535];
};

struct System_Uri_Fields {
    struct System_String_o* m_String;
    struct System_String_o* m_originalUnicodeString;
    struct System_UriParser_o* m_Syntax;
    struct System_String_o* m_DnsSafeHost;
    uint64_t m_Flags;
    struct System_Uri_UriInfo_o* m_Info;
    bool m_iriParsing;
};
struct System_Uri_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_System_Runtime_Serialization_ISerializable_GetObjectData;
};
struct System_Uri_c {
    Il2CppClass_1 _1;
    struct System_Uri_StaticFields* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Uri_VTable vtable;
};
struct System_Uri_o {
    System_Uri_c* klass;
    void* monitor;
    System_Uri_Fields fields;
};

struct System_Net_IPAddress_Fields {
    int64_t m_Address;
    struct System_String_o* m_ToString;
    int32_t m_Family;
    struct System_UInt16_array* m_Numbers;
    int64_t m_ScopeId;
    int32_t m_HashCode;
};
struct System_Net_IPAddress_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};
struct System_Net_IPAddress_c {
    Il2CppClass_1 _1;
    struct System_Net_IPAddress_StaticFields* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Net_IPAddress_VTable vtable;
};
struct System_Net_IPAddress_StaticFields {
    struct System_Net_IPAddress_o* Any;
    struct System_Net_IPAddress_o* Loopback;
    struct System_Net_IPAddress_o* Broadcast;
    struct System_Net_IPAddress_o* None;
    struct System_Net_IPAddress_o* IPv6Any;
    struct System_Net_IPAddress_o* IPv6Loopback;
    struct System_Net_IPAddress_o* IPv6None;
};
struct System_Net_IPAddress_o {
    System_Net_IPAddress_c* klass;
    void* monitor;
    System_Net_IPAddress_Fields fields;
};

struct System_Net_IPAddress_array {
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    System_Net_IPAddress_o* m_Items[65535];
};

struct System_Net_EndPoint_Fields {
};
struct System_Net_EndPoint_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_get_AddressFamily;
    VirtualInvokeData _5_Serialize;
    VirtualInvokeData _6_Create;
};
struct System_Net_EndPoint_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Net_EndPoint_VTable vtable;
};
struct System_Net_EndPoint_o {
    System_Net_EndPoint_c* klass;
    void* monitor;
    System_Net_EndPoint_Fields fields;
};
struct System_Net_IPEndPoint_Fields : System_Net_EndPoint_Fields {
    struct System_Net_IPAddress_o* m_Address;
    int32_t m_Port;
};
struct System_Net_IPEndPoint_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_get_AddressFamily;
    VirtualInvokeData _5_Serialize;
    VirtualInvokeData _6_Create;
};
struct System_Net_IPEndPoint_c {
    Il2CppClass_1 _1;
    struct System_Net_IPEndPoint_StaticFields* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Net_IPEndPoint_VTable vtable;
};
struct System_Net_IPEndPoint_o {
    System_Net_IPEndPoint_c* klass;
    void* monitor;
    System_Net_IPEndPoint_Fields fields;
};
struct System_Net_Sockets_Socket_Fields {
    void* _cachedTaskEventArgs;
    bool is_closed;
    bool is_listening;
    int32_t linger_timeout;
    int32_t addressFamily;
    int32_t socketType;
    int32_t protocolType;
    void* m_Handle;
    void* seed_endpoint;
    void* ReadSem;
    void* WriteSem;
    bool is_blocking;
    bool is_bound;
    bool is_connected;
    int32_t m_IntCleanedUp;
    bool connect_in_progress;
};
struct System_Net_Sockets_Socket_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_Dispose;
    VirtualInvokeData _5_Dispose;
};
struct System_Net_Sockets_Socket_c {
    Il2CppClass_1 _1;
    struct System_Net_Sockets_Socket_StaticFields* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_Net_Sockets_Socket_VTable vtable;
};
struct System_Net_Sockets_Socket_o {
    System_Net_Sockets_Socket_c* klass;
    void* monitor;
    System_Net_Sockets_Socket_Fields fields;
};
struct System_Net_Sockets_TcpClient_Fields {
    struct System_Net_Sockets_Socket_o* m_ClientSocket;
    bool m_Active;
    struct System_Net_Sockets_NetworkStream_o* m_DataStream;
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