#pragma once

// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Platform/IWindow.hpp>

#include <Gene2/Core/Math/Matrix4.hpp>
#include <Gene2/Core/Math/Vector3.hpp>

namespace g2 {
	class FreeCamera {
	public:
		FreeCamera(IWindow *window);

		void Tick(float dt);

		void SetProjection(const Matrix4& projection);
		Matrix4 GetProjection() const;

		Matrix4 CalculateView();

		void ToggleEnabled();
		bool IsEnabled() const;

	private:
		IWindow *m_window;
		Matrix4 m_projection;
		Vector3 m_rot, m_pos, m_up, m_dir;
		bool m_enabled;
	};
}
