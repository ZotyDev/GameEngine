#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"

namespace UE
{
	class Screen
	{
	public:
		Screen(Ref<Shader> shader, Ref<Framebuffer> framebuffer);
		~Screen();

		void Resize(UEUint32 width, UEUint32 height);

		void Bind();
		void Unbind();

		void RenderScreen();

		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Primitives::Quad> m_Mesh;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
	};
}