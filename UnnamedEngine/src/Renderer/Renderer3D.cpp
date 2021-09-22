#include "uepch.h"
#include "Renderer3D.h"

#include "Renderer/RenderCommand.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UE
{
	// Todo:
	// Send entire transform instead of position, rotation, size, etc..
	// Make shadows more abstract
	// Make material rendering better
	//	Automatically send values that start with "u_" to the shader
	// Support alpha blending (idea: if a predefined value is set on the material, the rendering is sorted);

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
	{}

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
		s_Data->LighViewProjectionMatrix = lightProjection * lightView;

		for (auto& it : s_Data->MaterialIndexMap)
		{
			Ref<Material> CurrentMaterial = it.first;

			Ref<Shader> MaterialShader;
			CurrentMaterial->GetShader("Shadow", MaterialShader);

			MaterialShader->Bind();

			MaterialShader->SetMat4("u_ViewProjection", s_Data->LighViewProjectionMatrix);

			for (auto& CurrentIndex : it.second)
			{
				glm::mat4 Transform = glm::mat4(1.0f);
				Transform = glm::translate(Transform, s_Data->PositionArray[CurrentIndex]);
				MaterialShader->SetMat4("u_Transform", Transform);
				s_Data->VaoArray[CurrentIndex]->Bind();
				RenderCommand::DrawIndexed(s_Data->VaoArray[CurrentIndex]);
			}
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

		for (auto& it : s_Data->MaterialIndexMap)
		{
			Ref<Material> CurrentMaterial = it.first;

			Ref<Shader> MaterialShader;
			CurrentMaterial->GetShader("Shader", MaterialShader);
			Ref<Texture2D> MaterialTexture;
			CurrentMaterial->GetTexture("Texture", MaterialTexture);

			MaterialShader->Bind();
			MaterialShader->SetInt("u_Texture1", 0);
			MaterialShader->SetInt("u_ShadowMap", 1);
			s_Data->ShadowBuffer->BindDepthAttachment(1);
			
			MaterialShader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
			MaterialShader->SetMat4("u_LightViewProjection", s_Data->LighViewProjectionMatrix);

			for (auto& CurrentIndex : it.second)
			{
				MaterialTexture->Bind();

				glm::mat4 Transform = glm::mat4(1.0f);
				Transform = glm::translate(Transform, s_Data->PositionArray[CurrentIndex]);
				Transform = glm::scale(Transform, s_Data->SizeArray[CurrentIndex]);
				Transform = glm::rotate(Transform, glm::radians(s_Data->RotationArray[CurrentIndex].x), glm::vec3(1.0f, 0.0f, 0.0f));
				Transform = glm::rotate(Transform, glm::radians(s_Data->RotationArray[CurrentIndex].y), glm::vec3(0.0f, 1.0f, 0.0f));
				Transform = glm::rotate(Transform, glm::radians(s_Data->RotationArray[CurrentIndex].z), glm::vec3(0.0f, 0.0f, 1.0f));
				MaterialShader->SetMat4("u_Transform", Transform);
				s_Data->VaoArray[CurrentIndex]->Bind();
				RenderCommand::DrawIndexed(s_Data->VaoArray[CurrentIndex]);
			}
		}

		// End of Rendering
		
		// Unbind Screen Framebuffer
		s_Data->ScreenFramebuffer->Unbind();

		// Clear Window Framebuffer
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		// Bind Screen Framebuffer Texture, Mesh and Camera ViewProjection to render it to the screen
		s_Data->ScreenFramebuffer->BindColorAttachment();
		//s_Data->ShadowBuffer->BindDepthAttachment(); // When this is enabled it is possible to see the shadow map
		s_Data->ScreenShader->Bind();
		s_Data->ScreenShader->SetMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		s_Data->ScreenMesh->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->ScreenMesh->VAO);

		s_Data->MaterialIndexMap.clear();
	}

	UEResult Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult::Success;
	}

	UEResult Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult::Success;
	}

	UEResult Renderer3D::Submit(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{	
		Ref<Shader> MaterialShader;
		if (material->GetShader("Shader", MaterialShader) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain shader");
			return UEResult::Error;
		}
		Ref<Texture2D> MaterialTexture;
		if (material->GetTexture("Texture", MaterialTexture) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain texture");
			return UEResult::Error;
		}

		s_Data->VaoArray[s_Data->Index] = vao;
		s_Data->ShaderArray[s_Data->Index] = MaterialShader;
		s_Data->TextureArray[s_Data->Index] = MaterialTexture;
		s_Data->PositionArray[s_Data->Index] = position;
		s_Data->SizeArray[s_Data->Index] = size;
		s_Data->RotationArray[s_Data->Index] = rotation;

		auto it = s_Data->MaterialIndexMap.find(material);
		if (it == s_Data->MaterialIndexMap.end())
		{
			std::vector<uint32_t> IndexMap;
			IndexMap.push_back(s_Data->Index);
			s_Data->MaterialIndexMap.insert({ material, IndexMap });
		}
		else
		{
			it->second.push_back(s_Data->Index);
		}

		s_Data->Index++;

		return UEResult::Success;
	}

	UEResult Renderer3D::Submit(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		Ref<Material> MaterialMaterial;
		if (s_MaterialLibrary->Get(material, MaterialMaterial) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not exist");
			return UEResult::Error;
		}

		Ref<Shader> MaterialShader;
		if (MaterialMaterial->GetShader("Shader", MaterialShader) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain shader");
			return UEResult::Error;
		}
		Ref<Texture2D> MaterialTexture;
		if (MaterialMaterial->GetTexture("Texture", MaterialTexture) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain texture");
			return UEResult::Error;
		}

		s_Data->VaoArray[s_Data->Index] = vao;
		s_Data->ShaderArray[s_Data->Index] = MaterialShader;
		s_Data->TextureArray[s_Data->Index] = MaterialTexture;
		s_Data->PositionArray[s_Data->Index] = position;
		s_Data->SizeArray[s_Data->Index] = size;
		s_Data->RotationArray[s_Data->Index] = rotation;

		auto it = s_Data->MaterialIndexMap.find(MaterialMaterial);
		if (it == s_Data->MaterialIndexMap.end())
		{
			std::vector<uint32_t> IndexMap;
			IndexMap.push_back(s_Data->Index);
			s_Data->MaterialIndexMap.insert({ MaterialMaterial, IndexMap });
		}
		else
		{
			it->second.push_back(s_Data->Index);
		}

		s_Data->Index++;

		return UEResult::Success;
	}

	UEResult Renderer3D::Submit(Entity entity, const Ref<Material> material)
	{
		return UEResult::Success;
	}

	UEResult Renderer3D::Submit(Entity entity)
	{
		return UEResult::Success;
	}
}
