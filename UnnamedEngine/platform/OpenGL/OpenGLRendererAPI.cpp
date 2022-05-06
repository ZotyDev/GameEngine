#include "uepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace UE
{
	void OpenGLMessageCallback
	(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei lenght,
		const char* message,
		const void* userParam
	)
	{
		UEString MessageSource;
		
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			MessageSource = "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			MessageSource = "WINDOW SYSTEM";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			MessageSource = "SHADER COMPILER";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			MessageSource = "THIRD_PARTY";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			MessageSource = "APPLICATION";
			break;
		case GL_DEBUG_SOURCE_OTHER:
		default:
			MessageSource = "Unknown";
			break;
		}

		UEString MessageType;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			MessageType = "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			MessageType = "DEPRECATED BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			MessageType = "UNDEFINED BHEVAIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			MessageType = "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			MessageType = "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_MARKER:
			MessageType = "MARKER";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			MessageType = "PUSH GROUP";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			MessageType = "POP GROUP";
			break;
		case GL_DEBUG_TYPE_OTHER:
		default:
			MessageType = "Unknown";
			break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			UE_CORE_CRITICAL("OpenGL: \n\t Source: {0}\n\t Type: {1}\n\t {2}", MessageSource, MessageType, message);
			return;
		case GL_DEBUG_SEVERITY_MEDIUM:
			UE_CORE_ERROR("OpenGL: \n\t Source: {0}\n\t Type: {1}\n\t {2}", MessageSource, MessageType, message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			UE_CORE_WARN("OpenGL: \n\t Source: {0}\n\t Type: {1}\n\t {2}", MessageSource, MessageType, message);
			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			UE_CORE_INFO("OpenGL: \n\t Source: {0}\n\t Type: {1}\n\t {2}", MessageSource, MessageType, message);
			return;
		default:
			UE_CORE_ERROR("OpenGL (unknown severity level): \n\t Source: {0}\n\t Type: {1}\n\t {2}", MessageSource, MessageType, message);
			break;
		}
	}


	void OpenGLRendererAPI::Init()
	{
		#if defined(UE_DEBUG)
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE);

		glVertexArrayAttribBinding(0, 0, 0);
	}

	void OpenGLRendererAPI::SetViewport(UEUint32 x, UEUint32 y, UEUint32 width, UEUint32 height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::GetViewport(UEUint32& width, UEUint32& height)
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

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, UEUint32 indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}