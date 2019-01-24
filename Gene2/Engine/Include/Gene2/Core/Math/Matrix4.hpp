// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	/**
	 * Represents a 4x4 floating point matrix.
	 */
	struct Matrix4 {
		float Elements[16]; ///< 1D array that stores elements continuously, Can be inded using the form `x + y * 4`.

		/**
		 * @brief Set this matrix to be the identity matrix of the form:
		 * \f[
		 * \begin{bmatrix}
		 * 1 & 0 & 0 & 0 \\
		 * 0 & 1 & 0 & 0 \\
		 * 0 & 0 & 1 & 0 \\
		 * 0 & 0 & 0 & 1
		 * \end{bmatrix}
		 * \f]
		 */
		void SetIdentity();
		
		/**
		* @brief Create a perspective projection matrix of the form:
		* \f[
		* \begin{bmatrix}
		* \frac{1}{aspect \times \tan{\frac{fov}{2}}} & 0 & 0 & 0 \\
		* 0 & \frac{1}{\tan{\frac{fov}{2}}} & 0 & 0 \\
		* 0 & 0 & \frac{-{(far + near)}}{far - near} & -{1} \\
		* 0 & 0 & \frac{-{(2 \times far \times near)}}{far - near} & 0
		* \end{bmatrix}
		* \f]
		* @param aspectRatio The aspect ratio of the screen (ratio of width to height)
		* @param fov Field of View, specified in degrees.
		* @param far Distance from the viewer to the far clipping plane (always positive)
		* @param near Distance from the viewer to the near clipping plane (always positive)
		* @return A perspective matrix of the above specified form, using the specified input values.
		*/
		static Matrix4 MakePerspective(
			const float& aspectRatio, 
			const float& fov, 
			const float& far, 
			const float& near
		);
		

		/**
		 * @brief Create a orthographic projection matrix of the form:
		 * \f[
		 * \begin{bmatrix}
		 * \frac{2}{right - left} & 0 & 0 & \frac{left + right}{left - right} \\
		 * 0 & \frac{2}{top - bottom} & 0 & \frac{bottom + top}{bottom - top} \\
		 * 0 & 0 & \frac{-2}{far - near} & \frac{far + near}{far - near} \\
		 * 0 & 0 & 0 & 1
		 * \end{bmatrix}
		 * \f]
		 * @param left Coordinate for the left hand side vertical clipping plane.
		 * @param right Coordinate for the right hand side vertical clipping plane.
		 * @param top Coordinate for the top horizontal clipping plane.
		 * @param bottom Coordinate for the bottom horizontal clipping plane.
		 * @param far Distance from the viewer to the far clipping plane (always positive)
		 * @param near Distance from the viewer to the near clipping plane (always positive)
		 * @return A orthographic matrix of the above specified form, using the specified input values.
		 */
		static Matrix4 MakeOrthographic(
			const float& left, 
			const float& right, 
			const float& top, 
			const float& bottom, 
			const float& far, 
			const float& near
		);
	};

	/**
	 * @brief Multiply together two matrices \f$left \times right\f$
	 * @param left The left hand side matrix.
	 * @param right The right hand side matrix
	 * @return The product of left and right.
	 */
	Matrix4 operator*(const Matrix4& left, const Matrix4& right);
}