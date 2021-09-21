#pragma once

#include "Renderer/Camera.h"

namespace UE
{
	class Camera3D : public Camera
	{
	public:
		Camera3D(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float nearClip = 0.1f, float farClip = 1000.0f, float fov = 45.0f);
		Camera3D();

	private:
		virtual void UpdateProjection();

	private:
		float m_FOV = 45.0f;
	};
}