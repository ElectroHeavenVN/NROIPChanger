// thanks to shmoo and joeyjurjens for the useful stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#if defined(__arm__)
#include "../Substrate/SubstrateHook.h"
#include "../Substrate/CydiaSubstrate.h"
#include "../Includes/Logger.h"
#elif defined(__aarch64__)
#include "../And64InlineHook/And64InlineHook.hpp"
#elif defined(__i386__)
	//TODO: x86 support
#error x86 is not supported yet
#elif defined(__x86_64__)
	//TODO: x86_64 support
#error x86_64 is not supported yet
#else
#error Unsupported architecture
#endif

void hook(void* offset, void* ptr, void** orig)
{
#if defined(__aarch64__)
	A64HookFunction(offset, ptr, orig);
#elif defined(__arm__)
	MSHookFunction(offset, ptr, orig);
#elif defined(__i386__)
	//TODO: x86 support
#elif defined(__x86_64__)
	//TODO: x86_64 support
#else 
#error Unsupported architecture
#endif
}

#define HOOK_ADDR(offset, ptr, orig) hook((void *)offset, (void *)ptr, (void **)&orig)
#define HOOK(lib, offset, ptr, orig) hook((void *)getAbsoluteAddress(lib, offset), (void *)ptr, (void **)&orig)
#define HOOK_NO_ORIG(lib, offset, ptr) hook((void *)getAbsoluteAddress(lib, offset), (void *)ptr, NULL)
#define HOOKSYM(lib, sym, ptr, org) hook(dlsym(dlopen(lib, 4), sym), (void *)ptr, (void **)&org)
#define HOOKSYM_NO_ORIG(lib, sym, ptr) hook(dlsym(dlopen(lib, 4), sym), (void *)ptr, NULL)

#endif //ANDROID_MOD_MENU_MACROS_H