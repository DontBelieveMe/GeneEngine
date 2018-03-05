#include <Math/Quaternion.h>
#include <Math/Functions.h>
#include <math.h>

using namespace Gene::Math;
using namespace Gene;

Quaternion::Quaternion(const Vector3& n, float a)
{
	float radians = Maths::ToRadians(a);
	float halfA = a * 0.5f;

	W = ::cosf(halfA);

	X = n.X * ::sinf(halfA);
	Y = n.Y * ::sinf(halfA);
	Z = n.Z * ::sinf(halfA);
}