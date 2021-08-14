#pragma once

#include "RenderCommand.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"

namespace UE
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void SetClearColor(glm::vec4 color);
		static void Clear();

		static void BeginRender(Camera& camera);
		static void EndRender();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
		
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
