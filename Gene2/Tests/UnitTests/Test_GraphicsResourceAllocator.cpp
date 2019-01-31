// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <catch2/catch.hpp>

#include <Gene2/Graphics/GraphicsResourceAllocator.hpp>

TEST_CASE("GraphicsResourceHandle can set index for positive values", "[graphicsresourcehandle]")
{
	g2::GraphicsResourceHandle handle;

	const int IN_INDEX = 1;
	
	handle.SetIndex(IN_INDEX);

	const int outIndex = handle.GetIndex();

	REQUIRE(outIndex == IN_INDEX);
}

TEST_CASE("GraphicsResourceHandle can set counter for positive values", "[graphicsresourcehandle]")
{
	g2::GraphicsResourceHandle handle;

	const g2::u8 IN_COUNTER = 123;

	handle.SetCounter(IN_COUNTER);

	const g2::u8 outCounter = handle.GetCounter();
	REQUIRE(outCounter == IN_COUNTER);
}

TEST_CASE("GraphicsResourceHandle can increment counter", "[graphicsresourcehandle]")
{
	g2::GraphicsResourceHandle handle;

	const g2::u8 IN_COUNTER = 32;
	handle.SetCounter(IN_COUNTER);
	handle.IncrementCounter();

	const g2::u8 outCounter = handle.GetCounter();

	REQUIRE(outCounter == (IN_COUNTER + 1));
}

TEST_CASE("GraphicsResourceHandle counter wraps on overflow", "[graphicsresourcehandle]")
{
	g2::GraphicsResourceHandle handle;
	const g2::u8 IN_COUNTER = 255;
	
	handle.SetCounter(IN_COUNTER);
	handle.IncrementCounter();

	const g2::u8 outCounter = handle.GetCounter();

	REQUIRE(outCounter == 0);
}

TEST_CASE("GraphicsResourceHandle index wraps on overflow", "[graphicsresourcehandle]")
{
	g2::GraphicsResourceHandle handle;
	const int IN_INDEX = (1 << 24) - 1;

	handle.SetIndex(IN_INDEX);
	int tmpIndex = handle.GetIndex();

	handle.SetIndex(handle.GetIndex() + 1);

	const int outIndex = handle.GetIndex();

	REQUIRE(outIndex == 0);
}