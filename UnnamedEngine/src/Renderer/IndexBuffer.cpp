#include "uepch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglIndexBuffer.h"

namespace UE
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: 
			return new OpenGLIndexBuffer(indices, count);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	};
}