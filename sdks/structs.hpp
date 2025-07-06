#pragma once
#include <map>
#include <set>
#include <iostream>
#include <corecrt_math_defines.h>

#include "../memory/memory.hpp"

// im lazy to clean this

// engine defines
class uclass;
class uobject;
class fmemory;
class ukismet_system_library;
class ukismet_string_library;
class ugameplay_statics;
class uscene_component;
class uprimitive_component;
class umesh_component;
class uskinned_mesh_component;
class uskeletal_mesh_component;
class aactor;
class aplayer_state;
class apawn;
class acharacter;
class aplayer_camera_manager;
class acontroller;
class aplayer_controller;
class uplayer;
class ulocal_player;
class ugame_instance;
class uworld;
class ugame_viewport_client;
class uengine;
class ucanvas;

// game defines
class afgf_character;
class afort_pawn;
class afort_player_pawn;
class afort_player_pawn_athena;


class ftext_data
{
public:
	char pad_0001[0x28]; //0x00
	wchar_t* name;       //0x28 
	__int32 length;      //0x40 

};

struct ftext {
	ftext_data* data;
	char unknown_data[0x10];

	wchar_t* get() const {
		if (data) return data->name;
		return nullptr;
	}
};

struct fname {
	fname() : comparison_index(uint32_t()) {};
	fname(uint32_t index) : comparison_index(index) {};

	bool operator==(const fname& other) const noexcept {
		return this->comparison_index == other.comparison_index;
	};

	uint32_t comparison_index;
};

struct fkey {
	fname name;
	char details[0x10];
};

template<class type>
struct tarray {
	type* data;
	int count;
	int max;

	tarray() : data(nullptr), count(0), max(0) { }
	tarray(type* data, int count, int max) : data(data), count(count), max(max) { }

	type operator[](int index) noexcept { return memory::read<type>(uintptr_t(data) + index * 0x8); }

	inline bool is_valid() const noexcept {
		return !(this->data == nullptr);
	}

	inline int num() const noexcept {
		return this->count;
	}

	inline bool is_valid_index(int index) const noexcept {
		return index < num();
	}

	inline void free() noexcept {
		fmemory::free(data);
		data = 0;
		count = max = 0;
	}
};

struct fstring : public tarray<wchar_t> {
	fstring() {}
	fstring(const wchar_t* other) {
		if (max = count = *other ? static_cast<int>(wcslen(other)) + 1 : 0)
			data = const_cast<wchar_t*>(other);
	};

	const wchar_t* c_str() const {
		return data;
	}

	std::string to_string() const {
		std::wstring w_str = data;
		return std::string(w_str.begin(), w_str.end());
	}
};

struct fvector {
	double x, y, z;

	fvector() : x(), y(), z() {}
	fvector(double x, double y, double z) : x(x), y(y), z(z) {}

	fvector operator + (const fvector& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
	fvector operator - (const fvector& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
	fvector operator * (double offset) const { return { this->x * offset, this->y * offset, this->z * offset }; }
	fvector operator / (double offset) const { return { this->x / offset, this->y / offset, this->z / offset }; }

	fvector& operator *= (const double other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
	fvector& operator /= (const double other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

	fvector& operator = (const fvector& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
	fvector& operator += (const fvector& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	fvector& operator -= (const fvector& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	fvector& operator *= (const fvector& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	fvector& operator /= (const fvector& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	operator bool() { return bool(this->x || this->y || this->z); }
	friend bool operator == (const fvector& a, const fvector& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	friend bool operator != (const fvector& a, const fvector& b) { return !(a == b); }
};

struct fvector2d {
	double x, y;

	fvector2d() : x(), y() {}
	fvector2d(double x, double y) : x(x), y(y) {}

	fvector2d operator + (const fvector2d& other) const { return { this->x + other.x, this->y + other.y }; }
	fvector2d operator - (const fvector2d& other) const { return { this->x - other.x, this->y - other.y }; }
	fvector2d operator * (double offset) const { return { this->x * offset, this->y * offset }; }
	fvector2d operator / (double offset) const { return { this->x / offset, this->y / offset }; }

	fvector2d& operator *= (const double other) { this->x *= other; this->y *= other; return *this; }
	fvector2d& operator /= (const double other) { this->x /= other; this->y /= other; return *this; }

	fvector2d& operator = (const fvector2d& other) { this->x = other.x; this->y = other.y; return *this; }
	fvector2d& operator += (const fvector2d& other) { this->x += other.x; this->y += other.y; return *this; }
	fvector2d& operator -= (const fvector2d& other) { this->x -= other.x; this->y -= other.y; return *this; }
	fvector2d& operator *= (const fvector2d& other) { this->x *= other.x; this->y *= other.y; return *this; }
	fvector2d& operator /= (const fvector2d& other) { this->x /= other.x; this->y /= other.y; return *this; }

	operator bool() { return bool(this->x || this->y); }
	friend bool operator == (const fvector2d& a, const fvector2d& b) { return a.x == b.x && a.y == a.y; }
	friend bool operator != (const fvector2d& a, const fvector2d& b) { return !(a == b); }
};

struct frotator {
	double pitch, yaw, roll;

	frotator() : pitch(), yaw(), roll() {}
	frotator(double pitch, double yaw, double roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	frotator operator + (const frotator& other) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
	frotator operator - (const frotator& other) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
	frotator operator * (double offset) const { return { this->pitch * offset, this->yaw * offset, this->roll * offset }; }
	frotator operator / (double offset) const { return { this->pitch / offset, this->yaw / offset, this->roll / offset }; }

	frotator& operator *= (const double other) { this->pitch *= other; this->yaw *= other; this->roll *= other; return *this; }
	frotator& operator /= (const double other) { this->pitch /= other; this->yaw /= other; this->roll /= other; return *this; }

	frotator& operator = (const frotator& other) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
	frotator& operator += (const frotator& other) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
	frotator& operator -= (const frotator& other) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
	frotator& operator *= (const frotator& other) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
	frotator& operator /= (const frotator& other) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

	operator bool() { return bool(this->pitch || this->yaw || this->roll); }
	friend bool operator == (const frotator& a, const frotator& b) { return a.pitch == b.pitch && a.yaw == b.yaw && a.roll == b.roll; }
	friend bool operator != (const frotator& a, const frotator& b) { return !(a == b); }
};

struct flinearcolor {
	float red, green, blue, alpha;

	flinearcolor() : red(0.f), green(0.f), blue(0.f), alpha(0.f) {}
	flinearcolor(float red, float green, float blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
};

struct fquat {
	float x, y, z, w;

	fquat() : x(0.f), y(0.f), z(0.f), w(0.f) {}
	fquat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct fmatrix {
	float m[4][4];

	inline fmatrix multiply(fmatrix matrix) {
		fmatrix pOut;
		pOut.m[0][0] = m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0] + m[0][3] * matrix.m[3][0];
		pOut.m[0][1] = m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1] + m[0][3] * matrix.m[3][1];
		pOut.m[0][2] = m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2] + m[0][3] * matrix.m[3][2];
		pOut.m[0][3] = m[0][0] * matrix.m[0][3] + m[0][1] * matrix.m[1][3] + m[0][2] * matrix.m[2][3] + m[0][3] * matrix.m[3][3];
		pOut.m[1][0] = m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0] + m[1][3] * matrix.m[3][0];
		pOut.m[1][1] = m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1] + m[1][3] * matrix.m[3][1];
		pOut.m[1][2] = m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2] + m[1][3] * matrix.m[3][2];
		pOut.m[1][3] = m[1][0] * matrix.m[0][3] + m[1][1] * matrix.m[1][3] + m[1][2] * matrix.m[2][3] + m[1][3] * matrix.m[3][3];
		pOut.m[2][0] = m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0] + m[2][3] * matrix.m[3][0];
		pOut.m[2][1] = m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1] + m[2][3] * matrix.m[3][1];
		pOut.m[2][2] = m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2] + m[2][3] * matrix.m[3][2];
		pOut.m[2][3] = m[2][0] * matrix.m[0][3] + m[2][1] * matrix.m[1][3] + m[2][2] * matrix.m[2][3] + m[2][3] * matrix.m[3][3];
		pOut.m[3][0] = m[3][0] * matrix.m[0][0] + m[3][1] * matrix.m[1][0] + m[3][2] * matrix.m[2][0] + m[3][3] * matrix.m[3][0];
		pOut.m[3][1] = m[3][0] * matrix.m[0][1] + m[3][1] * matrix.m[1][1] + m[3][2] * matrix.m[2][1] + m[3][3] * matrix.m[3][1];
		pOut.m[3][2] = m[3][0] * matrix.m[0][2] + m[3][1] * matrix.m[1][2] + m[3][2] * matrix.m[2][2] + m[3][3] * matrix.m[3][2];
		pOut.m[3][3] = m[3][0] * matrix.m[0][3] + m[3][1] * matrix.m[1][3] + m[3][2] * matrix.m[2][3] + m[3][3] * matrix.m[3][3];
		return pOut;
	}
};

struct ftransform {
	fquat rot;
	fvector translation;
	char pad_0001[0x8];
	fvector scale;
	char pad_0002[0x8];

	inline fmatrix to_matrix_with_scale() {
		fmatrix m{};
		m.m[3][0] = translation.x;
		m.m[3][1] = translation.y;
		m.m[3][2] = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m.m[0][0] = (1.0f - (yy2 + zz2)) * scale.x;
		m.m[1][1] = (1.0f - (xx2 + zz2)) * scale.y;
		m.m[2][2] = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m.m[2][1] = (yz2 - wx2) * scale.z;
		m.m[1][2] = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m.m[1][0] = (xy2 - wz2) * scale.y;
		m.m[0][1] = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m.m[2][0] = (xz2 + wy2) * scale.z;
		m.m[0][2] = (xz2 - wy2) * scale.x;

		m.m[0][3] = 0.0f;
		m.m[1][3] = 0.0f;
		m.m[2][3] = 0.0f;
		m.m[3][3] = 1.0f;

		return m;
	}
};

// engine enums
enum class ecollision_channel : uint8_t {
	ecc_world_static = 0,
	ecc_world_dynamic = 1,
	ecc_pawn = 2,
	ecc_visibility = 3,
	ecc_camera = 4,
	ecc_physics_body = 5,
	ecc_vehicle = 6,
	ecc_destructible = 7,
	ecc_engine_trace_channel1 = 8,
	ecc_engine_trace_channel2 = 9,
	ecc_engine_trace_channel3 = 10,
	ecc_engine_trace_channel4 = 11,
	ecc_engine_trace_channel5 = 12,
	ecc_engine_trace_channel6 = 13,
	ecc_game_trace_channel1 = 14,
	ecc_game_trace_channel2 = 15,
	ecc_game_trace_channel3 = 16,
	ecc_game_trace_channel4 = 17,
	ecc_game_trace_channel5 = 18,
	ecc_game_trace_channel6 = 19,
	ecc_game_trace_channel7 = 20,
	ecc_game_trace_channel8 = 21,
	ecc_game_trace_channel9 = 22,
	ecc_game_trace_channel10 = 23,
	ecc_game_trace_channel11 = 24,
	ecc_game_trace_channel12 = 25,
	ecc_game_trace_channel13 = 26,
	ecc_game_trace_channel14 = 27,
	ecc_game_trace_channel15 = 28,
	ecc_game_trace_channel16 = 29,
	ecc_game_trace_channel17 = 30,
	ecc_game_trace_channel18 = 31,
	ecc_overlap_all_deprecated = 32,
	ecc_max = 33
};