#pragma once
#include <windows.h>
#include <winternl.h>
#include <vector>
#include <intrin.h>

#include "..\globals.hpp"
#include "structs.hpp"

class uclass
{
public:
	char pad_0001[0x40];
	uclass* super_struct;
};

class uobject
{
public:
	void** vtable;
	int32_t flags;
	int32_t index;
	uclass* class_private;
	fname name;
	uobject* outer;

	template<typename type = uobject>
	static inline type* find_object(const wchar_t* name, uobject* outer = (uobject*)-1, bool exact = false) {
		typedef type* (__fastcall* static_find_object)(nullptr_t, uobject*, const wchar_t*, bool);
		auto static_find_object_fn = (static_find_object)(globals::base_address + globals::static_find_object);
		return static_find_object_fn(nullptr, outer, name, exact);
	}

	void process_event(uobject* function, void* args) {
		if (!this || !function) return;

		typedef void(__fastcall* process_event)(uobject*, uobject*, void*);
		auto process_event_fn = (process_event)(globals::base_address + globals::process_event);
		process_event_fn(this, function, args);
	}
};

class ukismet_system_library : public uobject
{
public:
	static ukismet_system_library* static_class() {
		static ukismet_system_library* klass = nullptr;
		if (!klass)
			klass = uobject::find_object<ukismet_system_library>(L"Engine.Default__KismetSystemLibrary");

		return klass;
	}

	uobject* get_outer_object(uobject* object);
};

class ukismet_string_library : public uobject
{
public:
	static ukismet_string_library* static_class() {
		static ukismet_string_library* klass = nullptr;
		if (!klass)
			klass = uobject::find_object<ukismet_string_library>(L"Engine.Default__KismetStringLibrary");

		return klass;
	}

	fname string_to_name(fstring in_string);
};

class ugameplay_statics : public uobject
{
public:
	static ugameplay_statics* static_class() {
		static ugameplay_statics* klass = nullptr;
		if (!klass)
			klass = uobject::find_object<ugameplay_statics>(L"Engine.Default__GameplayStatics");

		return klass;
	}

	bool object_is_a(uobject* object, uobject* object_class); // no need to call pe for is_a also
};

class uscene_component : public uobject
{
public:
	fvector get_socket_location(fname in_socket_name);
};

class uprimitive_component : public uscene_component {};

class umesh_component : public uprimitive_component {};

class uskinned_mesh_component : public umesh_component  {};

class uskeletal_mesh_component : public uskinned_mesh_component {};

class aactor : public uobject
{
public:
	uscene_component* root_component();
};

class apawn : public aactor {};

class acharacter : public apawn
{
public:
	uskeletal_mesh_component* mesh();
};

class aplayer_camera_manager : public aactor
{
public:
	fvector get_camera_location(); // no need to call pe to get cam location btw
};

class acontroller : public aactor
{
public:
	apawn* pawn();
};

class aplayer_controller : public acontroller
{
public:
	fvector2d world_to_screen(fvector world_location); // wrapper

	aplayer_camera_manager* player_camera_manager();

	bool project_world_location_to_screen(fvector world_location, fvector2d* screen_location, bool player_viewport_relative = false);
};

class uplayer : public uobject
{
public:
	aplayer_controller* player_controller();
};

class ulocal_player : public uplayer {};

class ugame_instance : public uobject
{
public:
	tarray<ulocal_player*> local_players();
};

class ulevel : public uobject
{
public:
	tarray<aactor*> actors();
};

class uworld : public uobject
{
public:
	static uworld* static_class() {
		uworld* cache_uworld = nullptr;
		if (!cache_uworld)
			cache_uworld = memory::read<uworld*>(globals::base_address + globals::uworld);

		return cache_uworld;
	}

	ugame_instance* game_instance();
	tarray<ulevel*> levels();
};

class ugame_viewport_client : public uobject
{
public:
	uworld* world();
	ugame_instance* game_instance();
	uengine* engine();
};

class uengine : public uobject
{
public:
	static uengine* static_class() {
		static uengine* engine_class = nullptr;
		if (!engine_class) {
			auto engine_static = uworld::static_class();
			if (!engine_static) return nullptr;

			auto game_instance = engine_static->game_instance();
			if (!game_instance) return nullptr;
			
			engine_class = (uengine*)ukismet_system_library::static_class()->get_outer_object(game_instance);
			if (!engine_class) return nullptr;
		}

		return engine_class;
	}

	ugame_viewport_client* game_viewport();
};

class ucanvas : public uobject
{
public:
	void draw_line(fvector2d start, fvector2d end, flinearcolor color = flinearcolor(1.f, 1.f, 1.f, 1.f), float thickness = 1.f);
};

inline aplayer_controller* player_controller = nullptr;