#include "uepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace UE
{
	void OpenGLMessageCallback
	(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int lenght,
		const char* message,
		const void* userParam
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			UE_CORE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_MEDIUM:
			UE_CORE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			UE_CORE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			UE_CORE_ERROR(message);
			return;
		}

		UE_CORE_ERROR("Unknown severity level!");
	}


	void OpenGLRendererAPI::Init()
	{
		#ifdef UE_DEBUG
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::GetViewport(uint32_t& width, uint32_t& height)
	{
		GLint t_viewport[4];
		glGetIntegerv(GL_VIEWPORT, t_viewport);
		width = t_viewport[2];
		height = t_viewport[3];	
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::CullFront()
	{
		glCullFace(GL_FRONT);
	}

	void OpenGLRendererAPI::CullBack()
	{
		glCullFace(GL_BACK);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}