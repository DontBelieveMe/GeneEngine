// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	struct Vector3
	{
		float X, Y, Z;

		Vector3();
		Vector3(const float& a);
		Vector3(const float& x, const float& y, const float& z);

		void Normalize();
		
		float Length() const;

		static float   DotProduct(const Vector3& left, const Vector3& right);
		static Vector3 CrossProduct(const Vector3& left, const Vector3& right);
	};
}