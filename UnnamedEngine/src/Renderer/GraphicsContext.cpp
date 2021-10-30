#include "uepch.h"
#include "Renderer/GraphicsContext.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLContext.h"
#endif
#if defined(UE_PLATFORM_VULKAN)
	#include "Vulkan/VulkanContext.h"
#endif

namespace UE
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		#endif
		#if defined(UE_PLATFORM_VULKAN)
		case RendererAPI::API::Vulkan:
			return CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
		#endif
		}

		UE_CORE_ASSERT(false, "Unkown RendererAPI");
		return nullptr;
	}
}