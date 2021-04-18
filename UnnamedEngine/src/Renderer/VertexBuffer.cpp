#include "VertexBuffer.h"

#include "logger/logger.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglVertexBuffer.h"

namespace UE
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		UE_LOG_FATAL("Unknown renderer!");
		return nullptr;
	};
}