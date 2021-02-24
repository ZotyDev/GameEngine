#include "IndexBuffer.h"

#include "Renderer.h"

#include "Platform/Opengl/OpenglIndexBuffer.h"

namespace UE
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
	};
}