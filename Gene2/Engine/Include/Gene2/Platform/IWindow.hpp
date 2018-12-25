// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/StdLib/Types.hpp>
#include <Gene2/Core/StdLib/String.hpp>
#include <Gene2/Core/StdLib/Memory.hpp>
#include <Gene2/Core/StdLib/Queue.hpp>

#include <Gene2/Platform/Event.hpp>

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
		static SharedPtr<IWindow> Create(const WindowConfig& windowConfig);

		IWindow(const WindowConfig& config);

		virtual void Show() = 0;
		virtual void Close() = 0;

		inline bool IsOpen() const { return m_bOpen; }

		inline u32 GetWidth() const { return m_config.Width; }
		inline u32 GetHeight() const { return m_config.Height; }
		
		bool PollEvent(Event& event);

	protected:
		virtual void Init() = 0;
		virtual void ProcessPlatformEvents() = 0;

		bool m_bOpen;
		WindowConfig m_config;

		Queue<Event> m_eventQueue;
	};
}