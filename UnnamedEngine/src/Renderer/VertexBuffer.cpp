#include "VertexBuffer.h"

#include "Core.h"

#include "Renderer.h"

#include "Platform/Opengl/OpenglVertexBuffer.h"

namespace UE
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
	};
}