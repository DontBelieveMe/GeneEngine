// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <vector>
#include <array>

namespace g2 {
	template <typename T>
	using Array = std::vector<T>;

	template <typename T, int Size>
	using FixedArray = std::array<T, Size>;
}