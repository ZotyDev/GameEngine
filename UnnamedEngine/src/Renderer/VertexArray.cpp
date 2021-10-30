#include "uepch.h"
#include "VertexArray.h"

#include "Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenglVertexArray.h"
#endif

namespace UE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexArray();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}