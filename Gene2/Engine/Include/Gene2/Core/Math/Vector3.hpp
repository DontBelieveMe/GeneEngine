// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	/**
	 * Represents a 3 component floating point Vector3
	 */
	struct Vector3
	{
		float X; ///< X Component of this Vector3
		float Y; ///< Y Component of this Vector3
		float Z; ///< Z Component of this Vector3

		/**
		 * @brief Initialize this Vector3, and set all components to zero.
		 */
		Vector3();

		/**
		 * @brief Initialize this Vector3, setting all components to the same scalar value.
		 * @param a The scalar value to set each component of this vector to.
		 */
		Vector3(const float& a);

		/**
		 * @brief Initialize this Vector3, setting the value of each component.
		 * @param x The value to set the X component to.
		 * @param y The value to set the Y component to.
		 * @param z The value to set the Z component to.
		 */
		Vector3(const float& x, const float& y, const float& z);

		/**
		 * @brief Normalize this Vector3 ( \f$\hat{v}\f$ ) in place.
		 */
		void  Normalize();

		/**
		 * @brief Calculate the magnitude/length ( \f$|v|\f$ of this Vector3.
		 * @return The scalar length of this Vector3
		 */
		float Length() const;

		/**
		 * @brief Calculate the dot product ( \f$left \cdot right\f$ ) of two vectors.
		 * @param left The left hand side of the dot product calculation.
		 * @param right The right hand side of the dot product calculation
		 * @return A new scalar float representing the dot product of the two specified Vector3's.
		 */
		static float   DotProduct(const Vector3& left, const Vector3& right);

		/**
		 * @brief Calculate the cross product ( \f$left \times right\f$ ) of two vectors.
		 * @param left The left hand side of the cross product calculation.
		 * @param right The right hand side of the cross product calculation
		 * @return A new Vector3 representing the cross product of the two specified Vector3's
		 */
		static Vector3 CrossProduct(const Vector3& left, const Vector3& right);
	};


	/**
	 * @brief Add together two Vector3's.
	 * @param left The left hand side of the addition.
	 * @param right The right hand side of the addition
	 * @return A new Vector3 representing the sum of left and right.
	 */
	Vector3 operator+(const Vector3& left, const Vector3& right);

	/**
	 * @brief Multiply together two Vector3's.
	 * @param left The left hand side vector.
	 * @param right The right hand side vector.
	 * @return A new Vector3 representing the product of left and right.
	 */
	Vector3 operator*(const Vector3& left, const Vector3& right);


	/**
	 * @brief Multiply together a Vector3 and a scalar value.
	 * @param left The left hand side vector.
	 * @param right The right hand side scalar.
	 * @return A new Vector3 representing the product of left and right.
	 */
	Vector3 operator*(const Vector3& left, const float& right);
}