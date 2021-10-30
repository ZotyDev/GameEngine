#include "uepch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "Opengl/OpenglIndexBuffer.h"
#endif

namespace UE
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL: 
			return new OpenGLIndexBuffer(indices, count);
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	};
}