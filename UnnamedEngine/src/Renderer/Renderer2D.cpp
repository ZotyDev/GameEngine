#include "uepch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/RenderCommand.h"

#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"
#include "Renderer/UniformBuffer.h"

#include "Core/GlobalConfig.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UE
{
	UEBool Renderer2D::Initialized = false;

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	struct Renderer2DData
	{
		static const UEUint32 MaxQuads = 20000;
		static const UEUint32 MaxVertices = MaxQuads * 4;
		static const UEUint32 MaxIndices = MaxQuads * 6;

		UEUint32 QuadIndexCount = 0;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::vector<Ref<Texture2D>> AlbedoArray;
		std::vector<Ref<Texture2D>> NormalArray;
		std::vector<Ref<Texture2D>> EmissiveArray;

		glm::vec4 QuadVertexPositions[4];

		Ref<Screen> Screen;
		struct CameraData
		{
			glm::mat4 ViewProjectionMatrix;
		} CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	Renderer2DData s_Data;

	void Renderer2D::Init(Ref<Screen> screen)
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "a_Position"	},
			{ ShaderDataType::Vec4, "a_Color"		}
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		UEUint32* QuadIndices = new UEUint32[s_Data.MaxIndices];

		UEUint32 Offset = 0;
		for (UEUint32 i = 0; i < s_Data.MaxIndices; i += 6)
		{
			QuadIndices[i + 0] = Offset + 0;
			QuadIndices[i + 1] = Offset + 1;
			QuadIndices[i + 2] = Offset + 2;
			
			QuadIndices[i + 3] = Offset + 2;
			QuadIndices[i + 4] = Offset + 3;
			QuadIndices[i + 5] = Offset + 0;

			Offset += 4;
		}

		Ref<IndexBuffer> QuadIB = IndexBuffer::Create(QuadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->AddIndexBuffer(QuadIB);
		delete[] QuadIndices;

		s_Data.QuadShader = Shader::Create();
		s_Data.QuadShader->LoadFromSource("assets/shader/quad");
		s_Data.QuadShader->Compile();

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
		s_Data.Screen = screen;

		Initialized = true;
	}

	void Renderer2D::Shutdown()
	{}

	void Renderer2D::OnWindowResize(UEUint32 width, UEUint32 height)
	{
		if (width != 0 && height != 0)
		{
			s_Data.Screen->Resize(width, height);
		}
	}

	void Renderer2D::BeginRender(Ref<Camera> camera)
	{
		Ref<Screen> CurrentScreen = s_Data.Screen;
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

		s_Data.CameraBuffer.ViewProjectionMatrix = camera->GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		// Empty rendering data
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndRender()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		// Bind screen
		s_Data.Screen->Bind();

		// Rendering
		UEUint32 DataSize = (UEUint32)((UEUint8*)s_Data.QuadVertexBufferPtr - (UEUint8*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, DataSize);
		
		s_Data.QuadShader->Bind();
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

		// End of rendering
		s_Data.Screen->Unbind();
		s_Data.Screen->RenderScreen();
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		constexpr UEUint32 QuadVertexCount = 4;
		const UEFloat TextureIndex = 0.0f;
		constexpr glm::vec2 TextureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		const float TilingFactor = 1.0f;

		glm::mat4 Transform = glm::mat4(1.0f);
		Transform = glm::translate(Transform, glm::vec3(position, 1.0f));
		Transform = glm::scale(Transform, glm::vec3(size, 1.0f));

		for (UEUint32 i = 0; i < QuadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = Transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, UEFloat tilingFactor, const glm::vec4 tintColor)
	{

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, UEFloat tilingFactor, const glm::vec4 tintColor)
	{

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, UEFloat tilingFactor, const glm::vec4& tintColor)
	{

	}

}