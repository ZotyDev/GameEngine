#pragma once

#include "core.h"

namespace UE
{
	class Camera
	{
	public:
		Camera(float fov, float width, float height, float nearClipPlane, float farClipPlane);
		Camera(float width, float height, float nearClipPlane, float farClipPlane);

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); };
		const glm::vec3& GetPosition() const { return m_Position; };

		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); };
		float GetRotation() const { return m_Rotation; };

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; };
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}