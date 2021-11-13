#include "uepch.h"
#include "Renderer/RendererAPI.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLRendererAPI.h"
#endif
#if defined(UE_PLATFORM_VULKAN)
	#include "Vulkan/VulkanRendererAPI.h"
#endif

namespace UE
{
	#if defined(UE_PLATFORM_OPENGL)
		RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	#elif defined(UE_PLATFORM_VULKAN)
		RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;
	#else
		RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;
		#error RendererAPI:None is not supported!
	#endif

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		#endif
		#if defined(UE_PLATFORM_VULKAN)
		case RendererAPI::API::Vulkan:
			return CreateScope<VulkanRendererAPI>();
		#endif
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}
}