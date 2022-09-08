#include "uepch.h"
#include "Camera.h"

#include "Core/GlobalConfig.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	Camera::Camera(UEFloat width, UEFloat height, glm::vec3 position, UEFloat nearClip, UEFloat farClip)
		: m_ViewportWidth(width), m_ViewportHeight(height), m_Position(position), m_NearClip(nearClip), m_FarClip(farClip)
	{}

	Camera::Camera()
	{
		m_ViewportWidth = GlobalConfig::Renderer::ScreenWidth;
		m_ViewportHeight = GlobalConfig::Renderer::ScreenHeight;
	}

	void Camera::UpdateView()
	{
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position + m_PositionOffset) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	glm::vec3 Camera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat Camera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, -m_Roll));
	}
}