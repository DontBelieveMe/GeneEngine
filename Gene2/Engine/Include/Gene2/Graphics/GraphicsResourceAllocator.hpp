// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "../Core/StdLib/Types.hpp"
#include "../Debug/Assert.hpp"

namespace g2 {
	/**
	 * Represents a generic handle to an array item. Managed by GraphicsResourceAllocator.
	 */
	class GraphicsResourceHandle {
	private:
		u32 m_handle = 0;

	public:
		/**
		 * @brief Set the index that this handle represents. While index is specified as int it can be no larger than
		 *        16777215 (\f$2^{24}\f$) (this is because handles are represented as 32 bit integers, and the other 
		 *        8 bits are used for a version counter).
		 * @param index The index that this handle represents (cannot be larger than 16777215, see brief).
		 */
		void SetIndex(int index);

		/**
		 * @brief Set the version counter for this handle. Version counters refer to how many times this handle has 
		 *        been used to reference different objects. Used to keep track of if a handle is valid or not.
		 * @param counter The version counter for this handle.
		 */
		void SetCounter(u8 counter);
		
		/**
		 * @brief Increment the version counter by one. Wraps around to zero again if the incremented value is larger than 255.
		 */
		void IncrementCounter();

		/**
		 * @brief Get the index that this handle represents. Will be no larger than 16777215 - see SetIndex for reasoning.
		 * @return The index stored by this handle.
		 */
		int GetIndex() const;

		/**
		 * @brief Get the version counter for this handle.
		 * @return The version counter of this handle.
		 */
		u8 GetCounter() const;
	};

	/**
	 * Manages handles for graphics objects - probably will be used in conjunction with an array of arbitrary objects - which
	 * the handle indices (which have been provided by this object) will point to.
	 */
	template <int Size>
	class GraphicsResourceAllocator {
	public:
		/**
		 * @brief Allocate a new GraphicsResourceHandle if it can.
		 * @return The allocated GraphicsResourceHandle.
		 */
		GraphicsResourceHandle Allocate()
		{
			G2_ASSERT(m_count < Size, "No suport currently for reusing handles.");

			GraphicsResourceHandle handle = m_handles[m_count];
			m_count++;

			return handle;
		}

		/**
		 * @brief Free an in use GraphicsResourceHandle, making it available for reuse.
		 * @param handle The handle to free.
		 */
		void Free(GraphicsResourceHandle handle)
		{
			G2_MARK_VARIABLE_UNUSED(handle);
			G2_ASSERT(false, "Free not currently supported for GraphicsResourceAllocator.");
		}

	private:
		GraphicsResourceHandle m_handles[Size];
		int                    m_count = 0;
	};
}