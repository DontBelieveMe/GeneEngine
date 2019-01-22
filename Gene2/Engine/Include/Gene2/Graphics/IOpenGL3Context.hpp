// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

namespace g2 {
	class IOpenGL3Context {
	public:
		IOpenGL3Context(void* windowHandle)
			: m_windowHandle(windowHandle){}

		virtual void Create() = 0;

	protected:
		void* m_windowHandle;
	};
}
