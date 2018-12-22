// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cstddef>
#include <cstdint>

namespace g2 {
	typedef int64_t   i64;
	typedef uint64_t  u64;

	typedef int32_t   i32;
	typedef uint32_t  u32;

	typedef int16_t   i16;
	typedef uint16_t  u16;

	typedef uint8_t   i8;
	typedef uint8_t   u8;

	static_assert(sizeof(float) == 4, "Float is not 32 bit on this architecture.");
	typedef float f32;
}