// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Graphics/IOpenGL3Context.hpp>

namespace g2 { namespace x11 {
	class X11OpenGL3Context : public IOpenGL3Context {
	public:
		X11OpenGL3Context(void* windowHandle, ContextAttributes attribs);

		virtual void Create() override;	
		virtual void SwapBuffers() override;
	};
}}
