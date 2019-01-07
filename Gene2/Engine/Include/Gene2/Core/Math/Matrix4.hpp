// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	struct Matrix4 {
		float Elements[16];

		void SetIdentity();
		
		static Matrix4 MakePerspective(
			const float& aspectRatio, 
			const float& fov, 
			const float& far, 
			const float& near
		);
		
		static Matrix4 MakeOrthographic(
			const float& left, 
			const float& right, 
			const float& top, 
			const float& bottom, 
			const float& far, 
			const float& near
		);
	};

	Matrix4 operator*(const Matrix4& left, const Matrix4& right);
}