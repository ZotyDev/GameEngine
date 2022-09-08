#include "uepch.h"
#include "Renderer.h"

#include "Renderer3D.h"
#include "Renderer2D.h"

#include "Core/GlobalConfig.h"

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

	void Renderer::OnWindowResize()
	{
		RenderCommand::SetViewport(0, 0, GlobalConfig::Renderer::ScreenWidth, GlobalConfig::Renderer::ScreenHeight);

		if (Renderer2D::Initialized)
		{
			Renderer2D::OnWindowResize(GlobalConfig::Renderer::DesiredWidth, GlobalConfig::Renderer::DesiredHeight);
		}
		
		if (Renderer3D::Initialized)
		{
			Renderer3D::OnWindowResize(GlobalConfig::Renderer::DesiredWidth, GlobalConfig::Renderer::DesiredHeight);
		}
	}

	void Renderer::SetClearColor(glm::vec4 color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::BeginRender(Ref<Camera> camera)
	{
		SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Clear();
		s_SceneData->ViewProjectionMatrix = camera->GetViewProjection();

		if (Renderer2D::Initialized)
		{
			Renderer2D::BeginRender(camera);
		}
		if (Renderer3D::Initialized)
		{
			Renderer3D::BeginRender(camera);
		}
	}

	void Renderer::EndRender()
	{
		if (Renderer2D::Initialized)
		{
			Renderer2D::EndRender();
		}
		if (Renderer3D::Initialized)
		{
			Renderer3D::EndRender();
		}
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}