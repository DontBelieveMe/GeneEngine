// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Core/StdLib/String.hpp>

using namespace g2;

String g2::SanitiseFormatString(String str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		char character = str[i];
		if (character == '{')
			str.insert(str.begin() + i, '{');
	}

	return str;
}