#include "uepch.h"
#include "Renderer/Camera2D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	Camera2D::Camera2D(UEFloat width, UEFloat height, glm::vec3 position, UEFloat nearClip, UEFloat farClip, UEFloat scale)
		: Camera(width, height, position, nearClip, farClip), m_Scale(scale)
	{
		Update();
	}

	Camera2D::Camera2D()
		: Camera()
	{
		Update();
	}

	void Camera2D::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		
		glm::vec4 tProjection;
		
		// Should work
		//tProjection = {
		//	0.0f,
		//	m_ViewportWidth,
		//	0.0f,
		//	m_ViewportHeight
		//};

		// Works
		tProjection = {
			-m_AspectRatio / m_Scale,
			m_AspectRatio / m_Scale,
			-1.0f / m_Scale,
			1.0f / m_Scale
		};

		m_Projection = glm::ortho(tProjection.x, tProjection.y, tProjection.z, tProjection.w, m_NearClip, m_FarClip);
	}
}