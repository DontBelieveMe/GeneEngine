// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cstdlib>
#include <assert.h>
#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Core/Utility/MacroFuncs.hpp>

#include <Gene2/Platform/Intrinsics.hpp>

#define G2_INTERNAL_CHECK(message, condition, ...) \
	do { if(!(condition)) { \
		const char* assertionMessage = G2_PP_CONCAT_STR(message, "\n\t`" G2_PP_STR(condition) "`" );\
		String customMsg = g2::FormatString(__VA_ARGS__); \
		G2_FATAL_LITERAL(g2::FormatString("{0}\n\t{1}", assertionMessage, customMsg)); \
		G2_DEBUG_BREAK(); \
	}} while(0)


#define G2_VERIFY(condition, ...) G2_INTERNAL_CHECK("Verification failed: ", condition, __VA_ARGS__)

#ifndef NDEBUG
	#define G2_ASSERT(condition, ...) G2_INTERNAL_CHECK("Assertion failed: ", condition, __VA_ARGS__)
#else
	#define G2_ASSERT(condition, ...)(void)(condition)
#endif