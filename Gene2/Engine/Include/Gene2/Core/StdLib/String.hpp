// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <string>

#include "StringStream.hpp"
#include "Array.hpp"

#include <Gene2/Platform/Intrinsics.hpp>

namespace g2 {
	/**
	 * Represents a char string - a continuous sequence of char values..
	 */
	using String = std::string;
	
	namespace internal {
		template <int ArrSize>
		void ToStringArray(FixedArray<String, ArrSize>& strArray, int& index) 
		{
			G2_MARK_VARIABLE_UNUSED(strArray);
			G2_MARK_VARIABLE_UNUSED(index);
		}

		template <int ArrSize, typename T, typename... Args>
		void ToStringArray(FixedArray<String, ArrSize>& strArray, int& index, const T& item, const Args&... args)
		{
			StringStream ss;
			ss << item;

			strArray[index++] = ss.str();
			ToStringArray<ArrSize, Args...>(strArray, index, args...);
		}

		template <int ArrSize, typename... Args>
		void ToStringArray(FixedArray<String, ArrSize>& arr, const Args&... args)
		{
			int i = 0;
			internal::ToStringArray<ArrSize, Args...>(arr, i, args...);
		}
	}

	/**
	 * @brief Overload of FormatString to allow the passing no arguments (useful for any varadic code that could potentially expand to nothing).
	 * @return An empty string.
	 */
	inline String FormatString() { return ""; }

	/**
	 * @brief Converts each format specifier (denoted by "{n}", where n is the index of the argument in the varadic arguments list)
	 *        in the format string (fmt) to the string representation of it's corresponding varadic argument.
	 * @param fmt The format string.
	 * @param args Zero or more values that represent the value of the corresponding format specifier.
	 * @return The formatted string, with the "{n}" replaced by the corresponding actual parameter.  
	 */
	template <typename... Args>
	String FormatString(const String& fmt, const Args&... args)
	{
		FixedArray<String, sizeof...(args)> argsArray;
		internal::ToStringArray<sizeof...(args), Args...>(argsArray, args...);

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
