#pragma once

#include "Renderer/Camera.h"

namespace UE
{
	class Camera3D : public Camera
	{
	public:
		Camera3D(UEFloat width, UEFloat height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), UEFloat nearClip = 0.1f, UEFloat farClip = 1000.0f, UEFloat fov = 45.0f);
		Camera3D();

		virtual void ZoomIn(UEFloat value) { m_FOV += -value; }
		virtual void ZoomOut(UEFloat value) { m_FOV -= -value; }
		virtual UEFloat GetZoom() { return m_FOV; }
		virtual void SetZoom(UEFloat zoom) { m_FOV = zoom; }

	private:
		virtual void UpdateProjection();

	private:
		UEFloat m_FOV = 45.0f;
	};
}