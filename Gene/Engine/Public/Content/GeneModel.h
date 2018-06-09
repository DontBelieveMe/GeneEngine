// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Platform/OpenGL.h>
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include <Core/Array.h>

namespace gene { namespace runtime {
	class GeneModel {
	public:
		Array<Vector3> Vertices;
        Array<Vector3> Normals;
        Array<Vector2> UVs;
        Array<GLuint> Indices;
	};
}}