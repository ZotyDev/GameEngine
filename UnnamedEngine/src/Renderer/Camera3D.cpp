#include "uepch.h"
#include "Renderer/Camera3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	Camera3D::Camera3D(float width, float height, glm::vec3 position, float nearClip, float farClip, float fov)
		: Camera(width, height, position, nearClip, farClip), m_FOV(fov)
	{
		Update();
	}

	Camera3D::Camera3D()
		: Camera()
	{
		Update();
	}

	void Camera3D::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}
}