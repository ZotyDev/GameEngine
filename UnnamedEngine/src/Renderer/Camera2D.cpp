#include "uepch.h"
#include "Renderer/Camera2D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	Camera2D::Camera2D(float width, float height, glm::vec3 position, float nearClip, float farClip, float scale)
		: Camera(width, height, position, nearClip, farClip), m_Scale(scale)
	{
		Update();
	}

	Camera2D::Camera2D()
		: Camera()
	{
		Update();
	}

	void Camera2D::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		//m_Projection = glm::ortho(0.0f, m_ViewportWidth, m_ViewportHeight, 0.0f, m_NearClip, m_FarClip);
		m_Projection = glm::ortho(-m_AspectRatio / m_Scale, m_AspectRatio / m_Scale, -1.0f / m_Scale, 1.0f / m_Scale, m_NearClip, m_FarClip);
	}
}