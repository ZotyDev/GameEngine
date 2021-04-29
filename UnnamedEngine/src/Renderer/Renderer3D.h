#pragma once

#include "Core/Base.h"

#include "Renderer/Camera3D.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"
#include "Renderer/Texture.h"

namespace UE
{
	class Renderer3D
	{
	public:
		static void Init(Ref<Shader> ScreenShader, Ref<Framebuffer> ScreenFramebuffer);
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(const Camera3D& camera);
		static void EndRender();
		static void Flush();

		static void DrawVao(const Ref<VertexArray>& vao, const Ref<Texture2D>& texture, const Ref<Shader>& shader, const glm::vec3& position);

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);
	private:
		struct Renderer3DData
		{
			glm::mat4 ViewProjectionMatrix;
			Ref<Framebuffer> ScreenFramebuffer;
			Ref<Framebuffer> ShadowBuffer;
			Ref<Shader> ShadowShader;
			Ref<Shader> ScreenShader;
			Ref<Primitives::Quad> ScreenMesh;

			std::array<Ref<VertexArray>, 32> VaoArray;
			std::array<Ref<Shader>, 32> ShaderArray;
			std::array<Ref<Texture2D>, 32> TextureArray;
			std::array<glm::vec3, 32> PositionArray;
			int Index;
		};

		static Scope<Renderer3DData> s_Data;
	};
}