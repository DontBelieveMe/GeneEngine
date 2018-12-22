// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/StdLib/Types.hpp>
#include <Gene2/Core/StdLib/String.hpp>

namespace g2 {
	struct WindowConfig {
		u32 Width;
		u32 Height;

		String Title;

		WindowConfig(u32 width, u32 height, const String& title)
			: Width(width), Height(height), Title(title) {}
	};

	class IWindow {
	public:
		static IWindow* Create(const WindowConfig& windowConfig);

		IWindow(const WindowConfig& config);

		virtual void Show() = 0;
		virtual void PollEvents() = 0;

		inline bool IsRunning() const { return m_bOpen; }
	protected:
		virtual void Init() = 0;

		bool m_bOpen;
		WindowConfig m_config;
	};
}