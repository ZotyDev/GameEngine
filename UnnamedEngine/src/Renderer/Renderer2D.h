#pragma once

#include "Renderer/Camera.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"
#include "Renderer/Texture.h"

#include "Renderer/Material.h"

#include "ECS/Entity.h"

namespace UE
{
	class Renderer2D
	{
	public:
		static void Init(Ref<Shader> screenShader, Ref<Framebuffer> screenFramebuffer, Ref<Shader> quadShader);
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(Ref<Camera> camera);
		static void EndRender();
		static void Flush();

		/*static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawSprite(const glm::mat4 transform, const glm::vec4& color);*/

	private:

		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TextureCoord;
			float TextureIndex;
			float TilingFactor;
		};

		struct Renderer2DData
		{
			glm::mat4 ViewProjectionMatrix;
			Ref<Shader> ScreenShader;
			Ref<Framebuffer> ScreenFramebuffer;
			Ref<Primitives::Quad> ScreenMesh;

			Ref<VertexArray> QuadVAO;
			Ref<Shader> QuadShader;

			uint32_t QuadIndexCount = 0;
		};

		static Scope<Renderer2DData> s_Data;
	};
}