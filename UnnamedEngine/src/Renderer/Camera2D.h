#pragma once

#include "Renderer/Camera.h"

namespace UE
{
	class Camera2D : public Camera
	{
	public:
		Camera2D(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float nearClip = 0.1f, float farClip = 1000.0f, float scale = 1.0f);
		Camera2D();

		virtual void ZoomIn(float value) { m_Scale += value * 0.015f; }
		virtual void ZoomOut(float value) { m_Scale -= value * 0.015f; }
		virtual float GetZoom() { return m_Scale; }

	private:
		virtual void UpdateProjection();
	private:
		float m_Scale = 1.0f;
	};
}