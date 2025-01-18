// thanks to shmoo and joeyjurjens for the useful stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#if defined(__aarch64__)
#include "And64InlineHook/And64InlineHook.hpp"
#elif defined(__arm__) || defined(__i386__) || defined(__x86_64__)
#include "Substrate/SubstrateHook.h"
#include "Substrate/CydiaSubstrate.h"
#include "Includes/Logger.h"
#else
#error Unsupported architecture
#endif

void hook(void* offset, void* ptr, void** orig)
{
#if defined(__aarch64__)
	A64HookFunction(offset, ptr, orig);
#elif defined(__arm__) || defined(__i386__) || defined(__x86_64__)
	MSHookFunction(offset, ptr, orig);
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