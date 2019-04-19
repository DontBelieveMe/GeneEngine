// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#include <Gene2/Scene/3D/FreeCamera.hpp>

using namespace g2;

FreeCamera::FreeCamera(IWindow* window)
	: m_window(window), m_enabled(true)
{
	G2_MARK_VARIABLE_UNUSED(m_window);
}

void FreeCamera::Tick(float dt)
{
	G2_MARK_VARIABLE_UNUSED(dt);

	if (!m_enabled)
		return;
}

Matrix4 FreeCamera::CalculateView()
{
	const Vector3 centre = m_pos + m_dir;
	return Matrix4::LookAt(m_pos, centre, m_up);
}

Matrix4 FreeCamera::GetProjection() const
{
	return m_projection;
}

void FreeCamera::SetProjection(const Matrix4& projection)
{
	m_projection = projection;
}

void FreeCamera::ToggleEnabled()
{
	m_enabled = !m_enabled;
}

bool FreeCamera::IsEnabled() const
{
	return m_enabled;
}