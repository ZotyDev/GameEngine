#pragma once

#include "Renderer/Screen.h"
#include "Renderer/Camera.h"

#include "Renderer/Texture.h"

namespace UE
{
	class Renderer2D
	{
	public:
		static void Init(Ref<Screen> screen);
		static void Shutdown();

		static void OnWindowResize(UEUint32 width, UEUint32 height);

		static void BeginRender(Ref<Camera> camera);
		static void EndRender();
		static void Flush();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, UEFloat tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, UEFloat tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, UEFloat tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/*static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawSprite(const glm::mat4 transform, const glm::vec4& color);*/
		
		static UEBool Initialized;
	};
}