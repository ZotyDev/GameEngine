#include "uepch.h"
#include "Renderer3D.h"

#include "Renderer/RenderCommand.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UE
{
	Scope<Renderer3D::Renderer3DData> Renderer3D::s_Data = CreateScope<Renderer3D::Renderer3DData>();
	Scope<MaterialLibrary> Renderer3D::s_MaterialLibrary = CreateScope<MaterialLibrary>();

	void Renderer3D::Init(Ref<Shader> ScreenShader, Ref<Framebuffer> ScreenFramebuffer)
	{
		s_Data->ScreenShader = ScreenShader;
		s_Data->ScreenFramebuffer = ScreenFramebuffer;
		s_Data->ScreenMesh = CreateRef<Primitives::Quad>(Primitives::Quad(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f)));
		
		FramebufferSpecification specs;
		specs.Width = 1024;
		specs.Height = 1024;
		specs.Attachments.Attachments.push_back(FramebufferTextureSpecification(FramebufferTextureFormat::Depth));
		s_Data->ShadowBuffer = Framebuffer::Create(specs);

		s_Data->ShadowShader = Shader::Create("data/shaders/shadow");

		Ref<Material> DefaultMaterial = CreateRef<Material>();
		DefaultMaterial->RegisterTexture("Texture", nullptr);
		DefaultMaterial->RegisterShader("Shader", nullptr);
		s_MaterialLibrary->Add("Default", DefaultMaterial);
	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::OnWindowResize(uint32_t width, uint32_t height)
	{
		s_Data->ScreenFramebuffer->Resize(width, height);
	}

	void Renderer3D::BeginRender(Ref<Camera> camera)
	{
		s_Data->ViewProjectionMatrix = camera->GetViewProjection();

		s_Data->VaoArray.fill(nullptr);
		s_Data->ShaderArray.fill(nullptr);
		s_Data->TextureArray.fill(nullptr);
		s_Data->PositionArray.fill(glm::vec3(0));
		s_Data->Index = 0;
	}

	void Renderer3D::EndRender()
	{
		Flush();
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	void Renderer3D::Flush()
	{
		// Store previous viewport
		uint32_t t_Width;
		uint32_t t_Height;
		RenderCommand::GetViewport(t_Width, t_Height);
		// Depth Framebuffer Rendering
		RenderCommand::SetViewport(0, 0, 1024, 1024);
		s_Data->ShadowBuffer->Bind();
		RenderCommand::ClearDepth();

		// Rendering
		//RenderCommand::CullFront();
		float t_NearPlane = 1.0f;
		float t_FarPlane = 100.0f;
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, t_NearPlane, t_FarPlane);
		glm::mat4 lightView = glm::lookAt(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightViewProjection = lightProjection * lightView;

		for (int i = 0; i < s_Data->Index; i++)
		{
			s_Data->TextureArray[i]->Bind();
			s_Data->ShaderArray[i]->Bind();
			s_Data->ShaderArray[i]->SetFloat3("u_Position", s_Data->PositionArray[i]);
			s_Data->ShaderArray[i]->SetMat4("u_ViewProjection", lightViewProjection);
			s_Data->VaoArray[i]->Bind();
			RenderCommand::DrawIndexed(s_Data->VaoArray[i]);
		}

		// End of Rendering

		// Set viewport to screen size
		RenderCommand::SetViewport(0, 0, t_Width, t_Height);

		// Bind Screen Framebuffer
		s_Data->ScreenFramebuffer->Bind();

		// Clear Screen Framebuffer to start rendering
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		
		// Rendering
		RenderCommand::CullBack();
		for (int i = 0; i < s_Data->Index; i++)
		{
			s_Data->ShaderArray[i]->Bind();
			s_Data->ShaderArray[i]->SetInt("u_Texture1", 0);
			s_Data->ShaderArray[i]->SetInt("u_ShadowMap", 1);
			s_Data->ShadowBuffer->BindDepthAttachment(1);
			s_Data->TextureArray[i]->Bind(0);
			s_Data->ShaderArray[i]->SetFloat3("u_Position", s_Data->PositionArray[i]);
			s_Data->ShaderArray[i]->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
			s_Data->ShaderArray[i]->SetMat4("u_LightViewProjection", lightViewProjection);
			s_Data->VaoArray[i]->Bind();
			RenderCommand::DrawIndexed(s_Data->VaoArray[i]);
		}

		// End of Rendering
		
		// Unbind Screen Framebuffer
		s_Data->ScreenFramebuffer->Unbind();

		// Clear Window Framebuffer
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		// Bind Screen Framebuffer Texture, Mesh and Camera ViewProjection to render it to the screen
		s_Data->ScreenFramebuffer->BindColorAttachment();
		//s_Data->ShadowBuffer->BindDepthAttachment();
		s_Data->ScreenShader->Bind();
		s_Data->ScreenShader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		s_Data->ScreenMesh->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->ScreenMesh->VAO);
	}

	void Renderer3D::DrawVao(const Ref<VertexArray>& vao, const Ref<Texture2D>& texture, const Ref<Shader>& shader, const glm::vec3& position)
	{
		s_Data->VaoArray[s_Data->Index] = vao;
		s_Data->ShaderArray[s_Data->Index] = shader;
		s_Data->TextureArray[s_Data->Index] = texture;
		s_Data->PositionArray[s_Data->Index] = position;
		s_Data->Index++;
	}

	UEResult Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult::Success;
	}

	UEResult Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const Ref<Material> material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult::Success;
	}
}
