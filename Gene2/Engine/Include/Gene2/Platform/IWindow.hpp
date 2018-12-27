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
		/**
		 * @brief Create a window for the current platform, but do not show it. 
		 *        Performs any window initialization
		 * @param windowConfig 
		 * @return A SharedPtr to the window implementation for this platform
		 */
		static SharedPtr<IWindow> Create(const WindowConfig& windowConfig);

		IWindow(const WindowConfig& config);

		virtual void Show() = 0;
		virtual void Close() = 0;

		/**
		 * @brief Gets if the window is currently open (displaying)
		 * @return If the window is open (aka displaying)
		 */
		inline bool IsOpen() const { return m_bOpen; }

		/**
		 * @brief Gets the width of the window (in pixels)
		 * @return The width of the window in pixels
		 */
		inline u32 GetWidth() const { return m_config.Width; }
	
		/**
		 * @brief Gets the height of the window (in pixels)
		 * @return The height of the window (in pixels)
		 */
		inline u32 GetHeight() const { return m_config.Height; }
		
		/**
		 * @brief Pops the top event off the event queue and returns it. 
		 *        The event queue may contain more than one event so this method should 
		 *        always be called inside a loop.
		 * @param event The reference that the returned value should be set to.
		 * @return True if an event has been popped off and return, false if the event queue is empty.
		 */
		bool PollEvent(Event& event);

	protected:
		virtual void Init() = 0;
		virtual void ProcessPlatformEvents() = 0;

		bool m_bOpen;
		WindowConfig m_config;

		Queue<Event> m_eventQueue;
	};
}