// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <cstddef>
#include <cstdint>

namespace g2 {
	/**
	 * Represents a signed 64-bit integer.
	 */
	typedef int64_t   i64;

	/**
	 * Represents a unsigned 64-bit integer.
	 */
	typedef uint64_t  u64;

	/**
	 * Represents a signed 32-bit integer.
	 */
	typedef int32_t   i32;

	/**
	 * Represents a unsigned 32 bit integer.
	 */
	typedef uint32_t  u32;

	/**
	 * Represents a signed 16-bit integer.
	 */
	typedef int16_t   i16;

	/**
	 * Represents a unsigned 16-bit integer.
	 */
	typedef uint16_t  u16;

	/**
	 * Represents a signed 8-bit integer
	 */
	typedef uint8_t   i8;

	/**
	 * Represents a unsigned 8-bit integer.
	 */
	typedef uint8_t   u8;

	static_assert(sizeof(float) == 4, "Float is not 32 bit on this architecture.");

	/**
	 * Represents a 32-bit floating point number.
	 */
	typedef float f32;
}