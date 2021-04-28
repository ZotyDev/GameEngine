#include "uepch.h"
#include "Renderer/RendererAPI.h"

#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace UE
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		}

		UE_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}
}