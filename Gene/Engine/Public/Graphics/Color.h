#pragma once

namespace Gene { namespace Graphics {
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

		/// Creates color with (floating point) rgba values in the range 0.0f -> 1.0f
		Color(float r, float g, float b, float a);

		/// Create color with (integer) rgba values in the range 0 -> 255
		Color(int r, int g, int b, int a);
		
		Color(unsigned int hex);

		Color();

		inline int R() const { return (Hex & 0xFF000000) >> 24; }
		inline int G() const { return (Hex & 0x00FF0000) >> 16; }
		inline int B() const { return (Hex & 0x0000FF00) >> 8; }
		inline int A() const { return (Hex & 0x000000FF); }

        inline ColorRGB GetRGBStruct() const
        {
            return ColorRGB(LinearR(), LinearG(), LinearB());
        }

		inline float LinearR() const { return static_cast<float>(R()) * OneOver255; }
		inline float LinearG() const { return static_cast<float>(G()) * OneOver255; }
		inline float LinearB() const { return static_cast<float>(B()) * OneOver255; }
		inline float LinearA() const { return static_cast<float>(A()) * OneOver255; }

		static unsigned int RGBAToHex(int r, int g, int b, int a);

		static const Color CornflowerBlue;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
	};
}}
