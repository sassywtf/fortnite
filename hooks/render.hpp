#pragma once
#include "../sdks/structs.hpp"
#include "../sdks/engine.hpp"
#include "../cheat/cheat.hpp"

namespace hooks {
	void render(ugame_viewport_client* game_viewport, ucanvas* canvas) {
		auto world = game_viewport->world();
		if (!world) return;

		globals::cached_world = (uint64_t)world;

		cheat_mgr::loop(world, canvas);
	}

	void (*opost_render)(ugame_viewport_client*, ucanvas*);
	void post_render(ugame_viewport_client* game_viewport, ucanvas* canvas) {
		render(game_viewport, canvas);
		return opost_render(game_viewport, canvas);
	}
}