#pragma once

#include "Core/Base.h"

#include "Renderer/Camera3D.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"

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

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

	private:
		struct Renderer3DData
		{
			glm::mat4 ViewProjectionMatrix;
			Ref<Framebuffer> ScreenFramebuffer;
			Ref<Shader> ScreenShader;
			Ref<Primitives::Quad> ScreenMesh;
		};

		static Scope<Renderer3DData> s_Data;
	};
}