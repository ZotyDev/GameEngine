#pragma once

#include "Renderer/Camera.h"

namespace UE
{
	class Camera2D : public Camera
	{
	public:
		Camera2D(UEFloat width, UEFloat height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), UEFloat nearClip = 0.1f, UEFloat farClip = 1000.0f, UEFloat scale = 1.0f);
		Camera2D();

		virtual void ZoomIn(float value) { m_Scale += value * 0.015f; }
		virtual void ZoomOut(float value) { m_Scale -= value * 0.015f; }
		virtual float GetZoom() { return m_Scale; }
		virtual void SetZoom(UEFloat zoom) { m_Scale = zoom; }

	private:
		virtual void UpdateProjection();
	private:
		UEFloat m_Scale = 1.0f;
	};
}