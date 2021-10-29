#include "uepch.h"
#include "Renderer/RendererAPI.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "OpenGL/OpenGLRendererAPI.h"
	#include "Vulkan/VulkanRendererAPI.h"
#endif

namespace UE
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:
			return CreateScope<VulkanRendererAPI>();
		#endif
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}
}