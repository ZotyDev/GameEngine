#pragma once

#include "Core.h"

#include "RenderCommand.h"

#include "Renderer/Camera3D.h"
#include "Renderer/Shader.h"

namespace UE
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(Camera3D& camera);
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
