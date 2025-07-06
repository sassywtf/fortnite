#include "cheat.hpp"

void cheat_mgr::skeleton(ucanvas* canvas, aplayer_controller* player_controller, uskeletal_mesh_component* skeletal_mesh_component, bool visible) {
	auto color = flinearcolor(1, 1, 1, 1);
	if (visible) color = flinearcolor(1, 0, 0, 1);

	struct bone_data {
		std::wstring name;
		fvector location;
		fvector2d screen;
	};

	std::vector<bone_data> bones = {
			{L"neck_01", {}, {}}, {L"pelvis", {}, {}}, {L"upperarm_l", {}, {}}, {L"upperarm_r", {}, {}},
			{L"lowerarm_l", {}, {}}, {L"lowerarm_r", {}, {}}, {L"hand_l", {}, {}}, {L"hand_r", {}, {}},
			{L"thigh_l", {}, {}}, {L"thigh_r", {}, {}}, {L"calf_l", {}, {}}, {L"calf_r", {}, {}},
			{L"foot_l", {}, {}}, {L"foot_r", {}, {}}
	};

	for (auto& bone : bones) {
		auto bone_name = ukismet_string_library::static_class()->string_to_name(bone.name.c_str());

		bone.location = skeletal_mesh_component->get_socket_location(bone_name);
		bone.screen = player_controller->world_to_screen(bone.location);
	}

#define draw_bone(start, end) \
        if (start.screen.x > 0 && start.screen.y > 0 && end.screen.x > 0 && end.screen.y > 0) \
            canvas->draw_line(start.screen, end.screen, color);

	draw_bone(bones[0], bones[1]);   // neck -> pelvis
	draw_bone(bones[0], bones[2]);   // neck -> upperarm_l
	draw_bone(bones[0], bones[3]);   // neck -> upperarm_r
	draw_bone(bones[2], bones[4]);   // upperarm_l -> lowerarm_l
	draw_bone(bones[3], bones[5]);   // upperarm_r -> lowerarm_r
	draw_bone(bones[4], bones[6]);   // lowerarm_l -> hand_l
	draw_bone(bones[5], bones[7]);   // lowerarm_r -> hand_r
	draw_bone(bones[1], bones[8]);   // pelvis -> thigh_l
	draw_bone(bones[1], bones[9]);   // pelvis -> thigh_r
	draw_bone(bones[8], bones[10]);  // thigh_l -> calf_l
	draw_bone(bones[9], bones[11]);  // thigh_r -> calf_r
	draw_bone(bones[10], bones[12]); // calf_l -> foot_l
	draw_bone(bones[11], bones[13]); // calf_r -> foot_r

#undef draw_bone
}

void cheat_mgr::loop(uworld* world, ucanvas* canvas) {
	auto game_instance = world->game_instance();
	if (!game_instance) return;

	auto local_players = game_instance->local_players();
	if (!local_players.num()) return;

	auto local_player = local_players[0];
	if (!local_player) return;

	player_controller = local_player->player_controller();
	if (!player_controller) return;

	auto player_camera_manager = player_controller->player_camera_manager();
	if (!player_camera_manager) return;

	auto pawn = (afort_player_pawn_athena*)player_controller->pawn();
	if (pawn && ugameplay_statics::static_class()->object_is_a(pawn, afort_player_pawn_athena::static_class())) {
		
		// whatever the fuck you want ...
	}

	// dont call GetAllActorsOfClass every frame i was being lazy
	auto levels = world->levels();
	if (!levels.num()) return;

	for (int i = 0; i < levels.num(); i++) {
		auto level = levels[i];
		if (!level) continue;

		auto actors = level->actors();
		if (!actors.num()) continue;

		for (int i = 0; i < actors.num(); i++) {
			auto actor = (afort_player_pawn_athena*)actors[i];
			if (!actor || actor == pawn) continue;

			// filter
			auto object_is_a_fort_player_pawn_athena = ugameplay_statics::static_class()->object_is_a(actor, afort_player_pawn_athena::static_class());
			if (object_is_a_fort_player_pawn_athena)
			{
				auto is_dead = actor->is_dead();
				if (is_dead) continue;

				auto get_team = actor->get_team();
				if (get_team == pawn->get_team()) continue;

				auto mesh = actor->mesh();
				if (!mesh) continue;

				auto is_visible = ufort_kismet_library::static_class()->check_line_of_sight_to_actor_with_channel(player_camera_manager->get_camera_location(), actor);

				skeleton(canvas, player_controller, mesh, is_visible);
			}
		}
	}
}