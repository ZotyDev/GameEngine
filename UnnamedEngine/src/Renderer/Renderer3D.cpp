#include "uepch.h"
#include "Renderer3D.h"

#include "Renderer/RenderCommand.h"


namespace UE
{
	Scope<Renderer3D::Renderer3DData> Renderer3D::s_Data = CreateScope<Renderer3D::Renderer3DData>();

	void Renderer3D::Init(Ref<Shader> ScreenShader, Ref<Framebuffer> ScreenFramebuffer)
	{
		s_Data->ScreenShader = ScreenShader;
		s_Data->ScreenFramebuffer = ScreenFramebuffer;
		s_Data->ScreenMesh = CreateRef<Primitives::Quad>(Primitives::Quad(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f)));
	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::OnWindowResize(uint32_t width, uint32_t height)
	{
		s_Data->ScreenFramebuffer->Resize(width, height);
	}

	void Renderer3D::BeginRender(const Camera3D& camera)
	{
		s_Data->ViewProjectionMatrix = camera.GetViewProjection();

		// Bind Framebuffer
		s_Data->ScreenFramebuffer->Bind();

		// Clear Framebuffer to start rendering
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
	}

	void Renderer3D::EndRender()
	{
		// Unbind Framebuffer
		s_Data->ScreenFramebuffer->Unbind();

		// Clear Screen buffer
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		// Bind Framebuffer Texture, Mesh and camera ViewProjection to render it to the screen
		s_Data->ScreenFramebuffer->BindColorAttachment();
		s_Data->ScreenShader->Bind();
		s_Data->ScreenShader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		s_Data->ScreenMesh->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->ScreenMesh->VAO);
	}

	void Renderer3D::Flush()
	{

	}

	void Renderer3D::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
