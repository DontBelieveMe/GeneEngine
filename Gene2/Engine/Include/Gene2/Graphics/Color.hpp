// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/StdLib/Types.hpp>

namespace g2 {
	/**
	 * Represents a color stored as a unsigned 32bit integer (each byte - left to right - corresponds
	 * to the R, G, B and A channels respectively.
	 */
	class Color {
	public:
		u32 Hex; //< Unsigned 32bit integer where each byte corresponds to the R, G, B, A components respectively.

		/**
		 * @brief Creates a color from normalized floating point values (in the range 0 -> 1)
		 * @param r The red component (in the range 0.0f -> 1.0f)
		 * @param g The green component (in the range 0.0f -> 1.0f)
		 * @param b The blue component (in the range 0.0f -> 1.0f)
		 * @param a The alpha component (in the range 0.0f -> 1.0f)
		 */
		Color(float r, float g, float b, float a);

		/**
		 * @brief Creates a color from byte values (in the range 0 -> 255)
		 * @param r The red component (in the range 0 -> 255)
		 * @param g The green component (in the range 0 -> 255)
		 * @param b The blue component (in the range 0 -> 255)
		 * @param a The alpha component (in the range 0 -> 255)
		 */
		Color(u8 r, u8 g, u8 b, u8 a);
		
		/**
		 * @brief Creates a color from a 32bit unsigned integer where each byte (left to right) corresponds
		 *        to the R, G, B and A components respectively.
		 * @param hex The integer value representing the color (each byte (in left to right order) represents the R, G, B and A components)
		 */
		Color(u32 hex);

		/**
		 * @brief Creates a color with all components zeroed (black with no alpha).
		 */
		Color();

		/**
		 * @brief Get the byte representing the red channel (range 0 -> 255)
		 * @return The red channel of this color.
		 */
		u8 GetRed() const;

		/**
		 * @brief Get the byte representing the green channel (range 0 -> 255)
		 * @return The green channel of this color
		 */
		u8 GetGreen() const;

		/**
		 * @brief Get the byte representing the blue channel (range 0 -> 255)
		 * @return The blue channel of this color
		 */
		u8 GetBlue() const;

		/**
		 * @brief Get the byte representing the alpha channel (range 0 -> 255)
		 * @return The alpha channel of this color.
		 */
		u8 GetAlpha() const;

		/**
		 * @brief Get the normalized floating point value for the red channel (range 0.0f -> 1.0f)
		 * @return The normalized floating point value for the red channel of this color.
		 */
		float GetNormalizedRed() const;
		
		/**
		* @brief Get the normalized floating point value for the green channel (range 0.0f -> 1.0f)
		* @return The normalized floating point value for the green channel of this color.
		*/
		float GetNormalizedGreen() const;

		/**
		* @brief Get the normalized floating point value for the blue channel (range 0.0f -> 1.0f)
		* @return The normalized floating point value for the blue channel of this color.
		*/
		float GetNormalizedBlue() const;

		/**
		* @brief Get the normalized floating point value for the alpha channel (range 0.0f -> 1.0f)
		* @return The normalized floating point value for the alpha channel of this color.
		*/
		float GetNormalizedAlpha() const;
	
	public:
		static const Color Red; ///< Full red. [Red: 255, Green: 0, Blue: 0, Alpha: 255]
		static const Color Green; ///< Full green. [Red: 0, Green: 255, Blue: 0, Alpha: 255]
		static const Color Blue; ///< Full blue. [Red: 0, Green: 0, Blue: 255, Alpha: 255]
		static const Color White; ///< Full white. [Red: 255, Green: 255, Blue: 255, Alpha: 255]
		static const Color Black; ///< Full black (no color) with full alpha. [Red: 0, Green: 0, Blue: 0, Alpha: 255]

	private:
		static constexpr float OneOver255 = 1.f / 255.f;
	};
}