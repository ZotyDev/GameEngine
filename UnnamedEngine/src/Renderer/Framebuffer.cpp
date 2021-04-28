#include "uepch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLFrameBuffer.h"

namespace UE
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: 
			return CreateRef<OpenGLFramebuffer>(specs);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}