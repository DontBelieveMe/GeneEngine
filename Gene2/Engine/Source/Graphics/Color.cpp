// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Graphics/Color.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

using namespace g2;

const Color Color::Red(0xFF0000FF);
const Color Color::Green(0x00FF00FF);
const Color Color::Blue(0x0000FFFF);
const Color Color::White(0xFFFFFFFF);
const Color Color::Black(0x000000FF);

Color::Color()
	: Hex(0x00000000)
{}

Color::Color(u32 hex)
	: Hex(hex)
{}

Color::Color(u8 r, u8 g, u8 b, u8 a)
	: Hex(r << 24 | g << 16 | b << 8 | a)
{}

Color::Color(float r, float g, float b, float a) 
{
	int rr = static_cast<int>(Math::Clamp(r, 0.0f, 1.0f) * 255);
	int gg = static_cast<int>(Math::Clamp(g, 0.0f, 1.0f) * 255);
	int bb = static_cast<int>(Math::Clamp(b, 0.0f, 1.0f) * 255);
	int aa = static_cast<int>(Math::Clamp(a, 0.0f, 1.0f) * 255);

	Hex = rr << 24 | gg << 16 | bb << 8 | aa;
}

u8 Color::GetRed() const
{
	return static_cast<u8>((Hex & 0xFF000000) >> 24);
}

u8 Color::GetGreen() const
{
	return static_cast<u8>((Hex & 0x00FF0000) >> 16);
}

u8 Color::GetBlue() const
{
	return static_cast<u8>((Hex & 0x0000FF00) >> 8);
}

u8 Color::GetAlpha() const
{
	return static_cast<u8>((Hex & 0x000000FF));
}

float Color::GetNormalizedRed() const
{
	return static_cast<float>(GetRed()) * OneOver255;
}

float Color::GetNormalizedGreen() const
{
	return static_cast<float>(GetGreen()) * OneOver255;
}

float Color::GetNormalizedBlue() const
{
	return static_cast<float>(GetBlue()) * OneOver255;
}

float Color::GetNormalizedAlpha() const
{
	return static_cast<float>(GetAlpha()) * OneOver255;
}
