#include <Gene2/Core/Math/Vector3.hpp>
#include <Gene2/Core/StdLib/Array.hpp>

#include <iostream>

int main()
{
	g2::Vector3 vec3(10.0f, 100.f, 13.f);
	
	g2::Array<g2::Vector3> dynamicArray;
	dynamicArray.push_back(vec3);

	g2::FixedArray<int, 3> fixedArray;
	fixedArray[0] = 123;

	system("pause");
    return 0;
}