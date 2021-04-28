#include "uepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/Opengl/OpenglVertexArray.h"

namespace UE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexArray();
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}