#include "uepch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglVertexBuffer.h"

namespace UE
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexBuffer(vertices, size);
		}

		UE_CORE_ASSERT(FALSE, "Unknown RendererAPI!");
		return nullptr;
	};
}