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

		Ref<Shader> GetShader() { return m_Shader; }
		Ref<Framebuffer> GetFramebuffer() { return m_Framebuffer; }

		void Resize(UEUint32 width, UEUint32 height);

		void Bind();
		void RenderScreen();

	private:
		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Primitives::Quad> m_Mesh;
	};
}