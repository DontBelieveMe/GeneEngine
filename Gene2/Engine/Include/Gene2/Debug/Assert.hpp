// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <cstdlib>
#include <assert.h>
#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Core/Utility/MacroFuncs.hpp>

#define G2_INTERNAL_CHECK(message, condition) \
	do { if(!(condition)) { \
		G2_FATAL(G2_PP_CONCAT_STR(message, G2_PP_STR(condition) )); \
		abort(); \
	}} while(0)

#define G2_VERIFY(condition) G2_INTERNAL_CHECK("Verification failed: ", condition)

#ifndef NDEBUG
	#define G2_ASSERT(condition) G2_INTERNAL_CHECK("Assertion failed: ", condition)
#else
	#define G2_ASSERT
#endif