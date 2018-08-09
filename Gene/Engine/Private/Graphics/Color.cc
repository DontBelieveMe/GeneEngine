// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Graphics/Color.h>
#include <Math/Functions.h>

using namespace gene::graphics;

const Color Color::CornflowerBlue (0x6495EDFF);
const Color Color::Red		      (0xFF0000FF);
const Color Color::Green		  (0x00FF00FF);
const Color Color::Blue			  (0x0000FFFF);
const Color Color::White		  (0xFFFFFFFF);
const Color Color::Black		  (0x000000FF);

Color::Color(float r, float g, float b, float a)
{
	using namespace gene;

	int rr = static_cast<int>(Maths::Clamp(r, 0.0f, 1.0f) * 255);
	int gg = static_cast<int>(Maths::Clamp(g, 0.0f, 1.0f) * 255);
	int bb = static_cast<int>(Maths::Clamp(b, 0.0f, 1.0f) * 255);
	int aa = static_cast<int>(Maths::Clamp(a, 0.0f, 1.0f) * 255);

	Hex = RGBAToHex(rr, gg, bb, aa);
}

Color::Color(int r, int g, int b, int a)
{
	Hex = RGBAToHex(r, g, b, a);
}

Color::Color(unsigned int hex): Hex(hex) { }

Color::Color() : Hex(0x00000000) {}

unsigned int Color::RGBAToHex(int r, int g, int b, int a)
{
	return r << 24 | g << 16 | b << 8 | a;
}

META_CLASS_REFLECT_IMPL(gene::graphics::Color)
	META_CLASS_DECLARE_MEMBER(int, Hex)
META_CLASS_END_REFLECT_IMPL()