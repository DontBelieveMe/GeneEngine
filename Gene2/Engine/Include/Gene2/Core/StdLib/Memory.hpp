// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <memory>

namespace g2 {
	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T, typename... Args>
	SharedPtr<T> MakeShared(Args&&... args) 
	{
		return std::make_shared<T>(args...);
	}

	template <typename T, typename... Args>
	UniquePtr<T> MakeUnique(Args&&... args) 
	{
		return std::make_unique<T>(args...);
	}
}