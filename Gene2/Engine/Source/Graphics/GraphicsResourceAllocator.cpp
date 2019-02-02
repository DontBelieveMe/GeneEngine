// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/GraphicsResourceAllocator.hpp>

using namespace g2;

void GraphicsResourceHandle::SetIndex(int index)
{
	m_handle = (m_handle & 0xFF000000) | (0x00FFFFFF & index);
}

void GraphicsResourceHandle::SetCounter(u8 counter)
{
	m_handle = (m_handle & 0x00FFFFFF) | (counter << 24);
}

void GraphicsResourceHandle::IncrementCounter()
{
	u8 c = GetCounter();
	c = c + 1;
	SetCounter(c);
}

int GraphicsResourceHandle::GetIndex() const
{
	return m_handle & 0x00FFFFFF;
}

u8 GraphicsResourceHandle::GetCounter() const 
{
	return (m_handle & 0xFF000000) >> 24;
}