// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "../Core/StdLib/Types.hpp"
#include "../Debug/Assert.hpp"

namespace g2 {
	class GraphicsResourceHandle {
	private:
		u32 m_handle = 0;

	public:
		void SetIndex(int index) {
			m_handle = (m_handle & 0xFF000000) | (0x00FFFFFF & index);
		}

		void SetCounter(u8 counter) {
			m_handle = (m_handle & 0x00FFFFFF) | (counter << 24);
		}

		void IncrementCounter() {
			u8 c = GetCounter();
			c = c + 1;
			SetCounter(c);
		}

		int GetIndex() {
			return m_handle & 0x00FFFFFF;
		}

		u8 GetCounter() {
			return (m_handle & 0xFF000000) >> 24;
		}
	};

	template <int Size>
	class GraphicsResourceAllocator {
	public:
		GraphicsResourceHandle Allocate()
		{

		}

		void Free(GraphicsResourceHandle handle)
		{

		}

	private:
		GraphicsResourceHandle m_handles[Size];
	};
}