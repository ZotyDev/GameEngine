#include "Camera.h"

namespace UE
{
	Camera::Camera(float fov, float width, float height, float nearClipPlane, float farClipPlane)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)width / (float)height, nearClipPlane, farClipPlane);
	}

	Camera::Camera(float width, float height, float nearClipPlane, float farClipPlane)
		: m_ViewMatrix(1.0f)
	{
		m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f , 1.0f, nearClipPlane, farClipPlane);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}