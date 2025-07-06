#include "game.hpp"

// ufort_kismet_library
bool ufort_kismet_library::check_line_of_sight_to_actor_with_channel(fvector source_pos, aactor* target, ecollision_channel target_filter_channel, aactor* source) {
	if (!this) return false;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"FortniteGame.FortKismetLibrary.CheckLineOfSightToActorWithChannel");

	struct {
		fvector source_pos;
		aactor* target;
		ecollision_channel target_filter_channel;
		aactor* source;
		bool return_value;
	} params = { source_pos, target, target_filter_channel, source };

	process_event(fn, &params);
	return params.return_value;
}

bool afort_pawn::is_dbno() {
	if (!this) return false;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"FortniteGame.FortPawn.IsDBNO");

	struct {
		bool return_value;
	} params;

	process_event(fn, &params);
	return params.return_value;
}

bool afort_pawn::is_dead() {
	if (!this) return false;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"FortniteGame.FortPawn.IsDead");

	struct {
		bool return_value;
	} params;

	process_event(fn, &params);
	return params.return_value;
}

char afort_pawn::get_team() {
	if (!this) return false;

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object(L"FortniteGame.FortPawn.GetTeam");

	struct {
		char return_value;
	} params;

	process_event(fn, &params);
	return params.return_value;
}