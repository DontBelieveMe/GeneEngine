#include <Gene2/Core/Math/Vector3.hpp>

#include <iostream>

int main()
{
	g2::Vector3 vector3(3.f, 1.f, 2.f);
	vector3.Normalize();

	system("pause");
    return 0;
}