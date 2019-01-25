// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <random>

namespace g2 {
	/**
	 * Generate pseudo-random data.
	 */
	class Random {
	private:
		static std::default_random_engine m_engine;

	public:
		/**
		 * @brief Seed the random number generator.
		 * @param seed The new seed of the random number generator.
		 */
		static void Seed(unsigned int seed);

		/**
		 * @brief Generate a random float in the range min -> max.
		 * @param min Smallest possible value that could be generated (minimum)
		 * @param max Largest possible value that could be generated (maximum)
		 * @return A random float in the range (min, max)
		 */
		static float FloatRange(const float& min, const float& max);
	
		/**
		 * @brief Generate a random integer in the range min -> max
		 * @param min Smallest possible value that could be generated (minimum)
		 * @param max Largest possible value that could be generated (maximum)
		 * @return A random integer in the range (min, max)
		 */
		static int   IntRange(const int& min, const int& max);
	};
}