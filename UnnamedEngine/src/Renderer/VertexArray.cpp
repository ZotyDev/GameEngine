#include "VertexArray.h"

#include "logger/logger.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglVertexArray.h"

namespace UE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		UE_LOG_FATAL("Unknown renderer!");
		return nullptr;
	}
}