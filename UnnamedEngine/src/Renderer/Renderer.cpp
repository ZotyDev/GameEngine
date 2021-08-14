#include "uepch.h"
#include "Renderer.h"

#include "Renderer3D.h"

namespace UE
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer3D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
		Renderer3D::OnWindowResize(width, height);
	}

	void Renderer::SetClearColor(glm::vec4 color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::BeginRender(Camera& camera)
	{
		SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Clear();
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndRender()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}