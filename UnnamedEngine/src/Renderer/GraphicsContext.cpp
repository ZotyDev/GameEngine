#include "uepch.h"
#include "Renderer/GraphicsContext.h"

#include "Renderer/Renderer.h"
#include "Platform/Opengl/OpenGLContext.h"

namespace UE
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		UE_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}