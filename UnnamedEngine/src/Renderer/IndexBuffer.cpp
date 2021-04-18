#include "IndexBuffer.h"

#include "logger/logger.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglIndexBuffer.h"

namespace UE
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		UE_LOG_FATAL("Unknown renderer!");
		return nullptr;
	};
}