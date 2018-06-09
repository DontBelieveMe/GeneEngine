// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <vector>
#include <unordered_map>

namespace gene {
	template <typename T>
	using Array = std::vector<T>;

	// This needs to move at some point...
	template <typename U, typename V>
	using HashMap = std::unordered_map<U, V>;
}