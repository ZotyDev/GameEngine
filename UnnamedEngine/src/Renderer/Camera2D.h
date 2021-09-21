#pragma once

#include "Renderer/Camera.h"

// Todo: take a look at the impact of using float position instead of pixels for this one

namespace UE
{
	class Camera2D : public Camera
	{
	public:
		Camera2D(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float nearClip = 0.1f, float farClip = 1000.0f);
		Camera2D();

	private:
		virtual void UpdateProjection();
	};
}