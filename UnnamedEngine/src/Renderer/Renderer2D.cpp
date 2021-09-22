#include "uepch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/RenderCommand.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UE
{
	Scope<Renderer2D::Renderer2DData> Renderer2D::s_Data = CreateScope<Renderer2D::Renderer2DData>();

	void Renderer2D::Init(Ref<Shader> screenShader, Ref<Framebuffer> screenFramebuffer, Ref<Shader> quadShader)
	{
		s_Data->ScreenShader = screenShader;
		s_Data->ScreenFramebuffer = screenFramebuffer;
		s_Data->ScreenMesh = s_Data->ScreenMesh = CreateRef<Primitives::Quad>(Primitives::Quad(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f)));
	}

	void Renderer2D::Shutdown()
	{}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
	{
		s_Data->ScreenFramebuffer->Resize(width, height);
	}

	void Renderer2D::BeginRender(Ref<Camera> camera)
	{
		s_Data->ViewProjectionMatrix = camera->GetViewProjection();
	}

	void Renderer2D::EndRender()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		// Bind screen framebuffer
		s_Data->ScreenFramebuffer->Bind();

		// Clear screen framebuffer to start rendering
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		// Rendering

		// Unbind screen framebuffer
		s_Data->ScreenFramebuffer->Unbind();

		// Clear window framebuffer
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		// Bind ScreenFramebuffer, ScreenTexture, ScreenMesh and ViewProjection to render to the window
		s_Data->ScreenFramebuffer->BindColorAttachment();
		s_Data->ScreenShader->Bind();
		s_Data->ScreenShader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		s_Data->ScreenMesh->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->ScreenMesh->VAO);
	}
}