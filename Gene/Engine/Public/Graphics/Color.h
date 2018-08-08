// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Math/Vector3.h>
#include <Runtime/Reflection.h>

namespace gene { namespace graphics {
    struct ColorRGB {
        float R, G, B;
        ColorRGB(float r, float g, float b): R(r), G(g), B(b) {}
    };

	class Color
	{
	private:
		static constexpr float OneOver255 = 1.f / 255.f;

	public:

		unsigned int Hex;

        /** Creates color with (floating point) rgba values in the range 0.0f -> 1.0f */
		Color(float r, float g, float b, float a);

        /** Create color with (integer) rgba values in the range 0 -> 255 */
		Color(int r, int g, int b, int a);
		
        /** Creates a color from the hex value secified in the hex format 0xRRGGBBAA*/
		Color(unsigned int hex);

        /** Default initalizes the color to black. */
		Color();

        /** Returns value for red component in the range 0 -> 255. */
		inline int R() const { return (Hex & 0xFF000000) >> 24; }

        /** Return the value for the green component in the range 0 -> 255 */
		inline int G() const { return (Hex & 0x00FF0000) >> 16; }

        /** Return the value for the blue component in the range 0 -> 255 */
		inline int B() const { return (Hex & 0x0000FF00) >> 8; }

        /** Return the value for the alpha component in the range 0 -> 255 */
		inline int A() const { return (Hex & 0x000000FF); }

        /** Return a 3D vector representing the R(x), G(y), B(z) components all in the range 0.f -> 1.f */
        inline Vector3 ToNormalizedVector3() const
        {
            return Vector3(LinearR(), LinearG(), LinearB());
        }

        /** Return the value for the red component in the range 0.f -> 1.f */
		inline float LinearR() const { return static_cast<float>(R()) * OneOver255; }

        /** Return the value for the green component in the range 0.f -> 1.f */
		inline float LinearG() const { return static_cast<float>(G()) * OneOver255; }

        /** Return the value for the blue component in the range 0.f -> 1.f */
		inline float LinearB() const { return static_cast<float>(B()) * OneOver255; }

        /** Return the value for the alpha component in the range 0.f -> 1.f */
		inline float LinearA() const { return static_cast<float>(A()) * OneOver255; }

        /** Combine the RGBA components (in the range 0 -> 255) into a single integer in the format 0xRRGGBBAA */
		static unsigned int RGBAToHex(int r, int g, int b, int a);

		static const Color CornflowerBlue;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
		
		META_CLASS_REFLECTED(gene::graphics::Color)
	};
}}
