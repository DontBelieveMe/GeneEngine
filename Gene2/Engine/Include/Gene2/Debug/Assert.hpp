// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <cstdlib>
#include <assert.h>
#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Core/Utility/MacroFuncs.hpp>

#include <Gene2/Platform/Intrinsics.hpp>

#define G2_INTERNAL_CHECK(message, condition, ...) \
	do { if(!(condition)) { \
		g2::String preassert = g2::FormatString("{0}: {1}", message, G2_PP_STR(condition));\
		G2_FATAL("{0}\n\t{1}", preassert, g2::FormatString(__VA_ARGS__));\
		G2_DEBUG_BREAK(); \
	}} while(0)


#define G2_VERIFY(condition, ...) G2_INTERNAL_CHECK("Verification failed: ", condition, __VA_ARGS__)

#ifndef NDEBUG
	#define G2_ASSERT(condition, ...) G2_INTERNAL_CHECK("Assertion failed: ", condition, __VA_ARGS__)
#else
	#define G2_ASSERT(condition, ...) G2_MARK_VARIABLE_UNUSED(condition)
#endif
