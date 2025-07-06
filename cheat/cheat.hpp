#pragma once
#include "..\sdks\game.hpp"

struct cheat_mgr {
	static void skeleton(ucanvas* canvas, aplayer_controller* player_controller, uskeletal_mesh_component* skeletal_mesh_component, bool visible);

	static void loop(uworld* world, ucanvas* canvas);
};