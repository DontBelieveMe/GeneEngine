// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <vector>
#include <array>

namespace g2 {
	/**
	 * Dynamic array, equivilant of std::vector<T>
	 */
	template <typename T>
	using Array = std::vector<T>;

	/**
	 * Fixed length array, equivilant of std::array<T, N> or T arr[N].
	 */
	template <typename T, int Size>
	using FixedArray = std::array<T, Size>;
}