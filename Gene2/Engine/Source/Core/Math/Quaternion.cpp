// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Core/Math/Quaternion.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

#include <Gene2/Platform/Intrinsics.hpp>

using namespace g2;

Quaternion::Quaternion(const Vector3& n, float a)
{
	float radians = Math::DegreesToRadians(a);
	float halfA = a * 0.5f;
	
	G2_MARK_VARIABLE_UNUSED(n);
	G2_MARK_VARIABLE_UNUSED(radians);
	G2_MARK_VARIABLE_UNUSED(halfA);
}