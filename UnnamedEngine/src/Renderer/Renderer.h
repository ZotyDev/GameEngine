#pragma once

#include "Core.h"

namespace UE
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		Vulkan = 2
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return mRendererAPI; };
	private:
		static RendererAPI mRendererAPI;
	};
}
