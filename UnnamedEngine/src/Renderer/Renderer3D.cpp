#include "uepch.h"
#include "Renderer3D.h"

#include "Renderer/RenderCommand.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/GlobalConfig.h"

namespace UE
{
	// Todo:
	// Make shadows more abstract
	// Make material rendering better
	//	Automatically send values that start with "u_" to the shader
	// Support alpha blending (idea: if a predefined value is set on the material, the rendering is sorted);

	Scope<Renderer3D::Renderer3DData> Renderer3D::s_Data = CreateScope<Renderer3D::Renderer3DData>();
	Scope<MaterialLibrary> Renderer3D::s_MaterialLibrary = CreateScope<MaterialLibrary>();
	
	UEBool Renderer3D::Initialized = false;

	void Renderer3D::Init(Ref<Screen> screen)
	{
		s_Data->CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData), 0);
		s_Data->Screen = screen;

		Initialized = true;
	}

	void Renderer3D::Shutdown()
	{}

	void Renderer3D::OnWindowResize(UEUint32 width, UEUint32 height)
	{
		if (width != 0 && height != 0)
		{
			s_Data->Screen->Resize(width, height);
		}
	}

	void Renderer3D::BeginRender(Ref<Camera> camera)
	{
		Ref<Screen> CurrentScreen = s_Data->Screen;
		{
			FramebufferSpecification spec = CurrentScreen->m_Framebuffer->GetSpecification();
			if (CurrentScreen->m_ViewportSize.x > 0.0f && CurrentScreen->m_ViewportSize.y > 0.0f && (spec.Width != CurrentScreen->m_ViewportSize.x || spec.Height != CurrentScreen->m_ViewportSize.y))
			{
				UEUint32 Width = (UEUint32)((UEFloat)CurrentScreen->m_ViewportSize.x / GlobalConfig::Renderer::PixelSize);
				UEUint32 Height = (UEUint32)((UEFloat)CurrentScreen->m_ViewportSize.y / GlobalConfig::Renderer::PixelSize);
				camera->SetViewportSize((UEFloat)Width, (UEFloat)Height);
				RenderCommand::SetViewport(0, 0, Width, Height);
				OnWindowResize(Width, Height);
			}
		}

		s_Data->CameraBuffer.ViewProjectionMatrix = camera->GetViewProjection();
		s_Data->CameraUniformBuffer->SetData(&s_Data->CameraBuffer, sizeof(Renderer3DData::CameraData));

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
		// Bind screen
		s_Data->Screen->Bind();
		
		// Start of rendering
		RenderCommand::CullBack();

		// Render background layer

		// Render opaque object layer

		// Render opaque particle layer

		// Render transparent object layer

		// Render transparent particle layer

		// Render special effect layer

		// Render overlay layer

		for (auto& it : s_Data->MaterialIndexMap)
		{
			Ref<Material> CurrentMaterial = it.first;

			Ref<Shader> MaterialShader;
			CurrentMaterial->GetShader("Shader", MaterialShader);
			Ref<Texture2D> MaterialTexture;
			CurrentMaterial->GetTexture("Texture", MaterialTexture);

			MaterialShader->Bind();

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

		// End of rendering
		s_Data->Screen->Unbind();
		s_Data->Screen->RenderScreen();

		s_Data->MaterialIndexMap.clear();
	}

	UEResult<> Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult<>::Success;
	}

	UEResult<> Renderer3D::DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		return UEResult<>::Success;
	}

	UEResult<> Renderer3D::Submit(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{	
		Ref<Shader> MaterialShader;
		if (!material->GetShader("Shader", MaterialShader))
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain shader");
			return UEResult<>::Error;
		}
		Ref<Texture2D> MaterialTexture;
		if (!material->GetTexture("Texture", MaterialTexture))
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain texture");
			return UEResult<>::Error;
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

		return UEResult<>::Success;
	}

	UEResult<> Renderer3D::Submit(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
	{
		Ref<Material> MaterialMaterial;
		if (!s_MaterialLibrary->Get(material, MaterialMaterial))
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not exist");
			return UEResult<>::Error;
		}

		Ref<Shader> MaterialShader;
		if (!MaterialMaterial->GetShader("Shader", MaterialShader))
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain shader");
			return UEResult<>::Error;
		}
		Ref<Texture2D> MaterialTexture;
		if (!MaterialMaterial->GetTexture("Texture", MaterialTexture))
		{
			UE_CORE_ERROR("Failed to submit to Renderer3D: material does not contain texture");
			return UEResult<>::Error;
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

		return UEResult<>::Success;
	}
}
