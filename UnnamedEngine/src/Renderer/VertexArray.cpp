#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/Opengl/OpenglVertexArray.h"

namespace UE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
	}
}