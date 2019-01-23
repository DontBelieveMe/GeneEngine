// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/StdLib/Array.hpp>

namespace g2 {
	class VertexAttribute {
	private:
	public:
	};

	class VertexDef {
	private:
		Array<VertexAttribute> m_attributes;

	public:
		void addAttribute();
	};
}