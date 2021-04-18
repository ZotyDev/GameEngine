#include "RendererAPI.h"

#include "Logger/Logger.h"

#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace UE
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}

		UE_LOG_FATAL("Failed to create RendererAPI!");
		return nullptr;
	}
}