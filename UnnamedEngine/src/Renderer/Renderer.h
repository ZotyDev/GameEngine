#pragma once

#include "Core.h"

#include "RenderCommand.h"

namespace UE
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender();
		static void EndRender();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};
}
