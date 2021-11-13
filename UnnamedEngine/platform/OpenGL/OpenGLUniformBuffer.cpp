#include "uepch.h"
#include "OpenGL/OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace UE
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(UEUint32 size, UEUint32 binding)
	{
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, UEUint32 size, UEUint32 offset)
	{
		glNamedBufferSubData(m_ID, offset, size, data);
	}
}