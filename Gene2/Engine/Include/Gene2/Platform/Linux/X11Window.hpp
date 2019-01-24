#pragma once

#include <Gene2/Platform/IWindow.hpp>

namespace g2 { namespace x11 {
	class X11Window : public IWindow {
	public:
		X11Window(const WindowConfig& config);
		
		virtual void Show() override;
		virtual void ProcessPlatformEvents() override;
		virtual void Close() override;

	protected:
		virtual void Init() override;
	};
}}
