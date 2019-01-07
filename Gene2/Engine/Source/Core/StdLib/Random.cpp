// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Core/StdLib/Random.hpp>

using namespace g2;

std::default_random_engine Random::m_engine;

void Random::Seed(unsigned int seed) {
	m_engine.seed(seed);
}

float Random::FloatRange(const float& min, const float& max) {
	std::uniform_real_distribution<float> x(min, max);
	return x(m_engine);
}

int Random::IntRange(const int& min, const int& max) {
	std::uniform_int_distribution<int> x(min, max);
	return x(m_engine);
}