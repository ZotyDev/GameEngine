#include "uepch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLTexture.h"
#endif
#if defined(UE_PLATFORM_VULKAN)
	#include "Vulkan/VulkanTexture.h"
#endif

namespace UE 
{
	Ref<Texture2D> Texture2D::Create()
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>();
		#endif
		#if defined(UE_PLATFORM_VULKAN)
		case RendererAPI::API::Vulkan:
			return CreateRef<VulkanTexture2D>();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}