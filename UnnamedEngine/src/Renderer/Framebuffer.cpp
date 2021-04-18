#include "Framebuffer.h"

#include "Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLFrameBuffer.h"

namespace UE
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(specs);
		}

		UE_LOG_FATAL("Unknown renderer!");
		return nullptr;
	}
}