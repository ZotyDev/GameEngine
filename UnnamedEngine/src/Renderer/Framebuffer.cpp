#include "uepch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "OpenGL/OpenGLFrameBuffer.h"
#endif

namespace UE
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: 
			return CreateRef<OpenGLFramebuffer>(specs);
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}