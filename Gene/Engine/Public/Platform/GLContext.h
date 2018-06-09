// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

namespace gene { namespace platform {
	struct GLContext {
		void *Context;
		int MajorVersion, MinorVersion;
	};
}}