#pragma once
#include <windows.h>
#include <winternl.h>
#include <vector>

#include "..\sdks\engine.hpp"
#include "..\sdks\game.hpp"

class ufort_kismet_library : public uobject
{
public:
	static ufort_kismet_library* static_class() {
		static ufort_kismet_library* klass = nullptr;
		if (!klass)
			klass = uobject::find_object<ufort_kismet_library>(L"FortniteGame.FortKismetLibrary");

		return klass;
	}

	bool check_line_of_sight_to_actor_with_channel(fvector source_pos, aactor* target, ecollision_channel target_filter_channel = ecollision_channel::ecc_visibility, aactor* source = nullptr);
};

class afgf_character : public acharacter {};

class afort_pawn : public afgf_character
{
public:
	bool is_dbno();
	bool is_dead();
	char get_team();
};

class afort_player_pawn : public afort_pawn {};

class afort_player_pawn_athena : public afort_player_pawn
{
public:
	static afort_player_pawn_athena* static_class() {
		static afort_player_pawn_athena* klass = nullptr;
		if (!klass)
			klass = uobject::find_object<afort_player_pawn_athena>(L"FortniteGame.FortPlayerPawnAthena");

		return klass;
	}
};