#pragma once

#include "Core/Base.h"

#include "Renderer/Screen.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"
#include "Renderer/Texture.h"
#include "Renderer/UniformBuffer.h"

#include "Renderer/Material.h"

namespace UE
{
	class Renderer3D
	{
	public:
		static void Init(Ref<Screen> screen);
		static void Shutdown();

		static void OnWindowResize(UEUint32 width, UEUint32 height);

		static void BeginRender(Ref<Camera> camera);
		static void EndRender();
		static void Flush();

		static UEResult<> DrawVAO(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult<> DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

		static UEResult<> Submit(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult<> Submit(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

		static UEBool Initialized;
	private:
		struct Renderer3DData
		{
			struct CameraData
			{
				glm::mat4 ViewProjectionMatrix;
			};
			CameraData CameraBuffer;

			Ref<Screen> Screen;

			std::array<Ref<VertexArray>, 32> VaoArray;
			std::array<Ref<Shader>, 32> ShaderArray;
			std::array<Ref<Texture2D>, 32> TextureArray;
			std::array<glm::vec3, 32> PositionArray;
			std::array<glm::vec3, 32> SizeArray;
			std::array<glm::vec3, 32> RotationArray;
			std::array<Ref<Material>, 32> MaterialArray;
			UEUint32 Index;

			std::unordered_map<Ref<Material>, std::vector<UEUint32>> MaterialIndexMap;

			Ref<UniformBuffer> CameraUniformBuffer;
		};

		static Scope<MaterialLibrary> s_MaterialLibrary;
		static Scope<Renderer3DData> s_Data;
	};
}