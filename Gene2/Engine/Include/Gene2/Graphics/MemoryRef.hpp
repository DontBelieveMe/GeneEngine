// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2
{
	struct MemoryRef
	{
		MemoryRef(void* address, size_t size)
		{
			Data = address;
			Size = size;
		}

		/**
		 * The memory data itself.
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