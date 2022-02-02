#include "uepch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenglVertexBuffer.h"
#endif

namespace UE
{
	Ref<VertexBuffer> VertexBuffer::Create(UEUint32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		#endif
		}

		UE_CORE_ASSERT(FALSE, "Unknown RendererAPI!");
		return nullptr;
	};

	Ref<VertexBuffer> VertexBuffer::Create(UEFloat* vertices, UEUint32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		#endif
		}

		UE_CORE_ASSERT(FALSE, "Unknown RendererAPI!");
		return nullptr;
	};
}