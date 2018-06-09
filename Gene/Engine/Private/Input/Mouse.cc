// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Input/Mouse.h>
#include <Platform/OS.h>

using namespace gene::input;

gene::platform::Window *Mouse::s_PrimaryWindow = nullptr;

void Mouse::SetPrimaryWindow(gene::platform::Window *window)
{
	Mouse::s_PrimaryWindow = window;
}