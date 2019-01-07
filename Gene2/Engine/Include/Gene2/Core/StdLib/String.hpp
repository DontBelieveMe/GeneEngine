// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <string>

#include "StringStream.hpp"
#include "Array.hpp"

#include <Gene2/Platform/Intrinsics.hpp>

namespace g2 {
	using String = std::string;
	
	namespace internal {
		template <int ArrSize, typename T, typename... Args>
		void ToStringArray(FixedArray<String, ArrSize>& strArray, int& index, const T& item, const Args&... args)
		{
			StringStream ss;
			ss << item;

			strArray[index++] = ss.str();
			ToStringArray(strArray, index, args...);
		}

		template <int ArrSize>
		void ToStringArray(FixedArray<String, ArrSize>& strArray, int& index) 
		{
			G2_MARK_VARIABLE_UNUSED(strArray);
			G2_MARK_VARIABLE_UNUSED(index);
		}
		
		template <int ArrSize, typename... Args>
		void ToStringArray(FixedArray<String, ArrSize>& arr, const Args&... args)
		{
			int i = 0;
			internal::ToStringArray(arr, i, args...);
		}
	}

	// This is to allow passing empty variadic template argument lists and variadic macro parameters
	// to this method, and still compile.
	// Initially implemented for assertion macros - no need to specify additional message, but you can
	// and it will format correctly as a format string.
	inline String FormatString() { return ""; }

	// #todo: implement -> complete format syntax checking
	template <typename... Args>
	String FormatString(const String& fmt, const Args&... args)
	{
		FixedArray<String, sizeof...(args)> argsArray;
		internal::ToStringArray(argsArray, args...);

		StringStream buff;
		for (size_t i = 0; i < fmt.length(); ++i)
		{
			char currentchar = fmt[i];

			if (currentchar == '{')
			{
				if (i + 1 < fmt.length())
				{
					if (fmt[i + 1] == '{')
					{
						i++;
						buff << '{';
						continue;
					}
				}
				else {
					continue;
				}

				String indexString;
				while (currentchar != '}') 
				{
					currentchar = fmt[++i];
					indexString += currentchar;
				}

				const int index = std::stoi(indexString);
				
				if (index < static_cast<int>(argsArray.size()) && index >= 0)
				{
					buff << argsArray[index];
				}
			}
			else {
				buff << currentchar;
			}
		}

		return buff.str();
	}
}