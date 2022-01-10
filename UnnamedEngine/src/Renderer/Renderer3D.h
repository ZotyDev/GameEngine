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

#include "ECS/Entity.h"

namespace UE
{
	class Renderer3D
	{
	public:
		static void Init(Ref<Screen> screen);
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(Ref<Camera> camera);
		static void EndRender();
		static void Flush();

		static UEResult DrawVAO(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult DrawVAO(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

		static UEResult Submit(const Ref<VertexArray>& vao, const Ref<Material>& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult Submit(const Ref<VertexArray>& vao, const std::string& material, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));
		static UEResult Submit(Entity entity, const Ref<Material> material);
		static UEResult Submit(Entity entity);

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
			uint32_t Index;

			std::unordered_map<Ref<Material>, std::vector<uint32_t>> MaterialIndexMap;

			Ref<UniformBuffer> CameraUniformBuffer;
			Ref<UniformBuffer> LightUniformBuffer;
		};

		static Scope<MaterialLibrary> s_MaterialLibrary;
		static Scope<Renderer3DData> s_Data;
	};
}