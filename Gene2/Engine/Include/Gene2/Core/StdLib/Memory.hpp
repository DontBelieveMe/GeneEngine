// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <memory>

namespace g2 {
	/**
	 * Smart ref counted pointer. Multiply SharedPtr<T>'s can point to the same value, 
	 * and the pointer is freed when it is no longer referenced. 
	 * Equivilant of std::shared_ptr<T>.
	 */
	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	/**
	 * Smart pointer for unique ownership of a pointer - cannot be copied & not ref counted.
	 * Pointer is freed when the smart pointer goes out of scope.
	 * Equivilant of std::unique_ptr<T>
	 */
	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	/**
	 * @brief Creates a g2::SharedPtr of type T
	 * @param args List of arguments of which type T will be created using.
	 * @return A g2::SharedPtr of type T.
	 */
	template <typename T, typename... Args>
	SharedPtr<T> MakeShared(Args&&... args) 
	{
		return std::make_shared<T>(args...);
	}

	/**
	 * @brief Creates a g2::UniquePtr of type T
	 * @param args List of arguments of which type T will be create using.
	 * @return A g2::UniquePtr of type T
	 */
	template <typename T, typename... Args>
	UniquePtr<T> MakeUnique(Args&&... args) 
	{
		return UniquePtr<T>(new T(std::forward<Args>(args)...));
	}
}
