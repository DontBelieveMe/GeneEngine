// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	template <typename T>
	struct Singleton 
	{
		static T* GetInstance() 
		{
			static T instance;
			return &instance;
		}
	};
}