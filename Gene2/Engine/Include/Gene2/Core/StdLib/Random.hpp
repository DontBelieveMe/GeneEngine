// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <random>

namespace g2 {
	class Random {
	private:
		static std::default_random_engine m_engine;

	public:
		static void Seed(unsigned int seed);

		static float FloatRange(const float& min, const float& max);
		static int   IntRange(const int& min, const int& max);
	};
}