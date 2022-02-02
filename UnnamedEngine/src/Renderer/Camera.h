#pragma once

#include "glm/glm.hpp"

namespace UE
{
	class Camera
	{
	public:
		Camera(UEFloat width, UEFloat height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), UEFloat nearClip = 0.1f, UEFloat farClip = 1000.0f);
		Camera();

		virtual ~Camera() = default;

		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		inline void SetViewportSize(UEFloat width, UEFloat height)
		{
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			Update();
		}

		void Update()
		{
			UpdateProjection();
			UpdateView();
		}

		virtual void ZoomIn(float value) = 0;
		virtual void ZoomOut(float value) = 0;
		virtual float GetZoom() = 0;
		virtual void SetZoom(UEFloat zoom) = 0;

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }
		const glm::vec3& GetPositionOffset() const { return m_PositionOffset; }
		void SetPositionOffset(const glm::vec3& positionOffset) { m_PositionOffset = positionOffset; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		void SetPitch(UEFloat pitch) { m_Pitch = pitch; }
		float GetYaw() const { return m_Yaw; }
		void SetYaw(UEFloat yaw) { m_Yaw = yaw; }
		float GetRoll() { return m_Roll; }
		void SetRoll(UEFloat roll) { m_Roll = roll; }

	private:
		virtual void UpdateProjection() = 0;
		void UpdateView();

	protected:
		UEFloat m_AspectRatio = 1.77f;
		UEFloat m_NearClip = 0.1f;
		UEFloat m_FarClip = 1000.0f;

		glm::mat4 m_ViewMatrix = {};
		glm::mat4 m_Projection = {};
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_PositionOffset = { 0.0f, 0.0f, 0.0f };

		UEFloat m_Pitch = 0.0f;
		UEFloat m_Yaw = 0.0f;
		UEFloat m_Roll = 0.0f;

		UEFloat m_ViewportWidth;
		UEFloat m_ViewportHeight;
	};
}