#pragma once

namespace Gene { namespace Platform {
	struct GLContext {
		void *Context;
		int MajorVersion, MinorVersion;
	};
}}