// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <string>
#include <sstream>

namespace gene {
	using String = std::string;

	template <typename T>
	std::string ToString(T value)
	{
	    std::ostringstream os;
	    os << value;
	    return os.str();
	}

	template <typename T>
	std::string ToHexString(T value)
	{
		std::stringstream stream;
		stream << std::hex << value;
		return stream.str();
	}
}