// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2
{
	/**
	 * A weak (non owning) reference to a block of memory.
	 * Does not store a copy of the data, only a pointer to it.
	 */
	struct MemoryRef
	{
		/**
		 * @brief Create a reference to the memory at the specified address.
		 * @param address The address to the data to reference.
		 * @param size The size of the data pointed to by the specified address. Specified in bytes.
		 */
		MemoryRef(void* address, size_t size)
		{
			Data = address;
			Size = size;
		}

		/**
		 * The address of the data.
		 */
		void* Data;

		/**
		 * The size of the memory block in bytes. For example for 
		 *		int x[3] = {1, 2, 3};
		 * this equals 12 - 3 elements of 4 bytes each.
		 */
		size_t Size;
	};
}