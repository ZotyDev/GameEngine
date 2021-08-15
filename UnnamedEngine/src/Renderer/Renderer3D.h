#pragma once

#include "Core/Base.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"
#include "Renderer/Texture.h"

#include "Renderer/Material.h"

namespace UE
{
	class Renderer3D
	{
	public:
		static void Init(Ref<Shader> ScreenShader, Ref<Framebuffer> ScreenFramebuffer);
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(Ref<Camera> camera);
		static void EndRender();
		static void Flush();

		static void DrawVao(const Ref<VertexArray>& vao, const Ref<Texture2D>& texture, const Ref<Shader>& shader, const glm::vec3& position);

		static UEResult DrawVAO(const Ref<VertexArray>& vao, const Ref<Material> material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

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
			std::array<glm::vec3, 32> SizeArray;
			std::array<glm::vec3, 32> RotationArray;
			std::array<Ref<Material>, 32> MaterialArray;
			int Index;
		};

		static Scope<MaterialLibrary> s_MaterialLibrary;
		static Scope<Renderer3DData> s_Data;
	};
}