#include "uepch.h"
#include "OpenglIndexBuffer.h"

#include <glad/glad.h>

namespace UE
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(UEUint32* indices, UEUint32 count) : mCount(count)
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(UEUint32), indices, GL_STATIC_DRAW);
	};

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &mID);
	};

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	};

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
}