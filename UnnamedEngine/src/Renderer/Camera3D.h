#pragma once

#include "Core/Base.h"
#include "glm/glm.hpp"

namespace UE
{
	class Camera3D
	{
	public:
		Camera3D(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float nearClip = 0.1f, float farClip = 1000.0f, float fov = 45.0f);
		Camera3D();

		virtual ~Camera3D() = default;

		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		inline void SetViewportSize(float width, float height)
		{
			m_ViewportWidth = width;
			m_ViewportHeight = height;
		}

		void Update()
		{
			UpdateProjection();
			UpdateView();
		}

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		void SetPitch(float pitch) { m_Pitch = pitch; }
		float GetYaw() const { return m_Yaw; }
		void SetYaw(float yaw) { m_Yaw = yaw; }
		float GetRoll() { return m_Roll; }
		void SetRoll(float roll) { m_Roll = roll; }

	private:
		void UpdateProjection();
		void UpdateView();

	private:
		float m_FOV = 45.0f;
		float m_AspectRatio = 1.77f;
		float m_NearClip = 0.1f;
		float m_FarClip = 1000.0f;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_Projection;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_Roll = 0.0f;

		float m_ViewportWidth = 1280;
		float m_ViewportHeight = 720;
	};
}