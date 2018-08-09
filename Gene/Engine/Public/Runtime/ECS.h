#pragma once

#include <Math/Vector3.h>
#include <Graphics/Color.h>

#include <Runtime/Reflection.h>

namespace gene 
{
	struct MemberObjectNested {
		Vector3 RandomVector3;
		int RandomInteger;

		META_CLASS_REFLECTED(gene::MemberObjectNested)
	};

	struct GameObject
	{
		Vector3 Position;
		graphics::Color Colour;
		int Test;
		MemberObjectNested ArbitraryObject;

		META_CLASS_REFLECTED(gene::GameObject)
	};
}
