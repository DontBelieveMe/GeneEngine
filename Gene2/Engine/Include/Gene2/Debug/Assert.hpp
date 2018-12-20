// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cstdlib>
#include <assert.h>
#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Core/Utility/MacroFuncs.hpp>

#include <Gene2/Platform/Intrinsics.hpp>

#define G2_INTERNAL_CHECK(message, condition) \
	do { if(!(condition)) { \
		G2_FATAL_LITERAL(G2_PP_CONCAT_STR(message, "\n\t`" G2_PP_STR(condition) "`" )); \
		G2_DEBUG_BREAK(); \
	}} while(0)


#ifndef NDEBUG
	#define G2_ASSERT(condition) G2_INTERNAL_CHECK("Assertion failed: ", condition)
	#define G2_VERIFY(condition) G2_INTERNAL_CHECK("Verification failed: ", condition)
#else
	#define G2_ASSERT
	#define G2_VERIFY(condition) (condition)
#endif