// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <queue>

namespace g2 {
	/**
	 * First in, First out data structure. Equivilant of std::queue<T>
	 */
	template <typename T>
	using Queue = std::queue<T>;
}