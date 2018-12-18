// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <string>

#include "StringStream.hpp"
#include "Array.hpp"

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
		void ToStringArray(FixedArray<String, ArrSize>& strArray, int& index) {}
		
		template <int ArrSize, typename... Args>
		void ToStringArray(FixedArray<String, ArrSize>& arr, const Args&... args)
		{
			int i = 0;
			internal::ToStringArray(arr, i, args...);
		}
	}

	// todo: implement -> complete format syntax checking
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

				int index = std::stoi(indexString);
				
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