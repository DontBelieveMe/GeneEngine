#include <Math/Quaternion.h>
#include <Math/Functions.h>
#include <math.h>

using namespace Gene::Math;

Quaternion::Quaternion(const Vector3& n, float a)
{
	float radians = Maths::ToRadians(a);
	float halfA = a * 0.5f;

	W = ::cosf(halfA);

	X = n.X * ::sin(halfA);
	Y = n.Y * ::sin(halfA);
	Z = n.Z * ::sin(halfA);
}