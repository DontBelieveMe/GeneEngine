// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#pragma once

namespace Gene { namespace Platform {
	struct GLContext {
		void *Context;
		int MajorVersion, MinorVersion;
	};
}}