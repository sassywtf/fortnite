#pragma once

namespace globals {
	inline uint64_t base_address = 0;
	inline uint64_t cached_world = 0;
	inline uint64_t old_post_render = 0;

	// main
	constexpr uint32_t uworld = 0x169D6108;
	constexpr uint32_t static_find_object = 0x20A0E4C;
	constexpr uint32_t process_event = 0x23B3394;
}