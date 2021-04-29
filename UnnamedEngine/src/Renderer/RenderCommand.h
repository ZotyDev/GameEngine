#pragma once

#include "RendererAPI.h"

namespace UE
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void GetViewport(uint32_t& width, uint32_t& height)
		{
			s_RendererAPI->GetViewport(width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void ClearDepth()
		{
			s_RendererAPI->ClearDepth();
		}

		static void CullFront() 
		{
			s_RendererAPI->CullFront();
		}

		static void CullBack()
		{
			s_RendererAPI->CullBack();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}