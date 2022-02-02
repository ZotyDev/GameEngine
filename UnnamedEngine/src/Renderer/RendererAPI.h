#pragma once

#include <glm/glm.hpp>

#include "Renderer/VertexArray.h"

// Todo:
// Enable/Disable wire rendering

namespace UE
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(UEUint32 x, UEUint32 y, UEUint32 width, UEUint32 height) = 0;
		virtual void GetViewport(UEUint32& width, UEUint32& height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void ClearDepth() = 0;
		virtual void CullFront() = 0;
		virtual void CullBack() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, UEUint32 indexCount = 0) = 0;

		static API GetAPI() { return s_API; };
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}