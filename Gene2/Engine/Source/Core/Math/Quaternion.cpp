#include <Gene2/Core/Math/Quaternion.hpp>
#include <Gene2/Core/StdLib/Math.hpp>

using namespace g2;

Quaternion::Quaternion(const Vector3& n, float a)
{
	(void)n;
	float radians = Math::DegreesToRadians(a); (void)radians;
	float halfA = a * 0.5f; (void)halfA;
}