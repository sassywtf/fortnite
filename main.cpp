#include <windows.h>
#include <iostream>

#include "globals.hpp"

//#include "memory/memory.hpp"

#include "sdks/structs.hpp"
#include "sdks/engine.hpp"

#include "hooks/render.hpp"

// how to use: add your own hook func and read/write memory

/*
ported this from my valorant to ue5, same shit very easy to use, if you want to switch this to valorant ue4.27 very easy just look at the docs
*/

bool DllMain(long long hinstDLL, uint32_t fdwReason, long long lpvReserved) {
	if (fdwReason != DLL_PROCESS_ATTACH) return true;

	globals::base_address = memory::base_address(L"FortniteClient-Win64-Shipping.exe");
	if (!globals::base_address) return false;

	auto viewport = uengine::static_class()->game_viewport();
	if (!viewport) return false;

	if (!memory::shadow_vt((uintptr_t)viewport, 0x398 / 8, hooks::post_render, (void**)&hooks::opost_render, (void**)&globals::old_post_render, true)) return false;

	return true;
}