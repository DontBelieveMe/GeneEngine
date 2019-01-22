// Copyright 2017-2019 Barney Wilks. All Rights Reserved
#pragma once

#include <Gene2/Graphics/IOpenGL3Context.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace g2 { namespace win32 {
	class Win32OpenGL3Context : public IOpenGL3Context {
	public:
		Win32OpenGL3Context(void* windowHandle);

		virtual void Create() override;

	private:
		HDC m_hdc;
		HGLRC m_context;
	};
}}