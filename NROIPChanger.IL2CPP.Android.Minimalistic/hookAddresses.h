#ifndef HOOKADDRESSES_H
#define HOOKADDRESSES_H
#include <vector>
#include "Includes/Utils.h"

std::vector<DWORD> hookAddresses;

#define TARGET_LIB_NAME "libil2cpp.so"
#define DEF_ADDR(name, index) DWORD name##_address() { return getAbsoluteAddress(TARGET_LIB_NAME, hookAddresses.at(index)); }

DEF_ADDR(System_String__CreateString_utf8, 0)
DEF_ADDR(System_String__CreateString_utf16, 1)
DEF_ADDR(System_Net_Sockets_TcpClient__Connect, 2)

#undef DEF_ADDR
#undef TARGET_LIB_NAME
#endif //HOOKADDRESSES_H
