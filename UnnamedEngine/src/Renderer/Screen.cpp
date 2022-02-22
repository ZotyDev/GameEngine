#include "uepch.h"
#include "Renderer/Screen.h"

#include "Renderer/RenderCommand.h"

namespace UE
{
	Screen::Screen(Ref<Shader> shader, Ref<Framebuffer> framebuffer)
		: m_Shader(shader), m_Framebuffer(framebuffer)
	{
		m_Mesh = CreateRef<Primitives::Quad>(Primitives::Quad(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f)));
	}

	Screen::~Screen()
	{}

	void Screen::Resize(UEUint32 width, UEUint32 height)
	{
		m_Framebuffer->Resize(width, height);
	}

	void Screen::Bind()
	{
		// Bind screen framebuffer
		m_Framebuffer->Bind();

		// Clear screen frambuffer
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();	
	}

	void Screen::Unbind()
	{
		// Unbind screen frambuffer
		m_Framebuffer->Unbind();
	}

	void Screen::RenderScreen()
	{
		// Clear target frambuffer
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		// Bind framebuffer info
		m_Framebuffer->BindColorAttachment();
		m_Shader->Bind();
		m_Mesh->VAO->Bind();

		// Render screen framebuffer into target framebuffer
		RenderCommand::DrawIndexed(m_Mesh->VAO);
	}
}