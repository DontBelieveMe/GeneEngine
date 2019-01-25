// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include "String.hpp"

namespace g2 {
	class File {
	public:
		static String ReadAllText(const char* filepath);
	};
}