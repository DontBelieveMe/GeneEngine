// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <memory>

namespace g2 {
	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;
}