#include "uepch.h"
#include "Camera3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	Camera3D::Camera3D(float width, float height, glm::vec3 position, float nearClip, float farClip, float fov)
		: m_ViewportWidth(width), m_ViewportHeight(height), m_Position(position), m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip)
	{
		UpdateProjection();
		UpdateView();
	}

	Camera3D::Camera3D()
	{
		UpdateProjection();
		UpdateView();
	}

	void Camera3D::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void Camera3D::UpdateView()
	{
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	glm::vec3 Camera3D::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera3D::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera3D::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat Camera3D::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, -m_Roll));
	}
}