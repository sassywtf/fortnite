#include "engine.hpp"

// ukismet_system_library
uobject* ukismet_system_library::get_outer_object(uobject* object) {
	if (!this || !object) return nullptr;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.KismetSystemLibrary.GetOuterObject");

	struct {
		uobject* object;
		uobject* return_value;
	} params = { object };

	process_event(fn, &params);
	return params.return_value;
}

// ukismet_string_library
fname ukismet_string_library::string_to_name(fstring in_string) {
	if (!this) return fname();

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.KismetStringLibrary.Conv_StringToName");

	struct {
		fstring in_string;
		fname return_value;
	} params = { in_string };

	process_event(fn, &params);
	return params.return_value;
}

// ugameplay_statics
bool ugameplay_statics::object_is_a(uobject* object, uobject* object_class) {
	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.GameplayStatics.ObjectIsA");

	struct {
		uobject* object;
		uobject* object_class;
		bool return_value;
	} params = { object, object_class };

	process_event(fn, &params);
	return params.return_value;
}

//uscene_component
fvector uscene_component::get_socket_location(fname in_socket_name) {
	if (!this) return fvector();

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.SceneComponent.GetSocketLocation");

	struct {
		fname in_socket_name;
		fvector return_value;
	} params = { in_socket_name };

	process_event(fn, &params);
	return params.return_value;
}

// aactor
uscene_component* aactor::root_component() {
	if (!this) return nullptr;

	return reinterpret_cast<uscene_component*>(memory::read<uintptr_t>(uintptr_t(this) + 0x1b0));
}

// acharacter
uskeletal_mesh_component* acharacter::mesh() {
	if (!this) return nullptr;

	return reinterpret_cast<uskeletal_mesh_component*>(memory::read<uintptr_t>(uintptr_t(this) + 0x328));
}

// aplayer_camera_manager
fvector aplayer_camera_manager::get_camera_location() {
	if (!this) return fvector();

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.PlayerCameraManager.GetCameraLocation");

	struct {
		fvector return_value;
	} params;

	process_event(fn, &params);
	return params.return_value;
}

apawn* acontroller::pawn() {
	if (!this) return nullptr;

	return reinterpret_cast<apawn*>(memory::read<uintptr_t>(uintptr_t(this) + 0x2e8));
}

// aplayer_controller
fvector2d aplayer_controller::world_to_screen(fvector world_location) {
	if (!this) return fvector2d();

	fvector2d output{};
	if (project_world_location_to_screen(world_location, &output)) return output;
	return fvector2d();
}

aplayer_camera_manager* aplayer_controller::player_camera_manager() {
	if (!this) return nullptr;

	return reinterpret_cast<aplayer_camera_manager*>(memory::read<uintptr_t>(uintptr_t(this) + 0x360));
}

bool aplayer_controller::project_world_location_to_screen(fvector world_location, fvector2d* screen_location, bool player_viewport_relative) {
	if (!this) return false;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.PlayerController.ProjectWorldLocationToScreen");

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relative;
		bool return_value;
	} params = { world_location, {}, false };

	process_event(fn, &params);

	if (screen_location) 
		*screen_location = params.screen_location;

	return params.return_value;
}

// uplayer
aplayer_controller* uplayer::player_controller() {
	if (!this) return nullptr;

	return reinterpret_cast<aplayer_controller*>(memory::read<uintptr_t>(uintptr_t(this) + 0x30));
}

// ugame_instance
tarray<ulocal_player*> ugame_instance::local_players() {
	if (!this) return {};

	return memory::read<tarray<ulocal_player*>>(uintptr_t(this) + 0x38);
}

// ulevel
tarray<aactor*> ulevel::actors() {
	if (!this) return {};

	return memory::read<tarray<aactor*>>(uintptr_t(this) + 0x98);
}

// uworld
ugame_instance* uworld::game_instance() {
	if (!this) return nullptr;

	return reinterpret_cast<ugame_instance*>(memory::read<uintptr_t>(uintptr_t(this) + 0x1f0));
}

tarray<ulevel*> uworld::levels() {
	if (!this) return {};

	return memory::read<tarray<ulevel*>>(uintptr_t(this) + 0x190);
}

// ugame_viewport_client
uworld* ugame_viewport_client::world() {
	if (!this) return nullptr;

	return reinterpret_cast<uworld*>(memory::read<uintptr_t>(uintptr_t(this) + 0x78));
}

ugame_instance* ugame_viewport_client::game_instance() {
	if (!this) return nullptr;

	return reinterpret_cast<ugame_instance*>(memory::read<uintptr_t>(uintptr_t(this) + 0x80));
}

uengine* ugame_viewport_client::engine() {
	if (!this) return nullptr;

	return reinterpret_cast<uengine*>(ukismet_system_library::static_class()->get_outer_object(game_instance())); // no need to call GetOuterObject just read outer from uobject
}

// uengine
ugame_viewport_client* uengine::game_viewport() {
	if (!this) return nullptr;

	return reinterpret_cast<ugame_viewport_client*>(memory::read<uintptr_t>(uintptr_t(this) + 0xa20));
}

// ucanvas
void ucanvas::draw_line(fvector2d start, fvector2d end, flinearcolor color, float thickness) {
	if (!this) return;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"Engine.Canvas.K2_DrawLine");

	struct {
		fvector2d start;
		fvector2d end;
		float thickness;
		flinearcolor color;
	} params = { start, end, thickness, color };

	process_event(fn, &params); // better not to use pe
}