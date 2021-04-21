#include "OpenglVertexArray.h"

namespace UE
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case UE::ShaderDataType::Float:		return GL_FLOAT;
		case UE::ShaderDataType::Float2:	return GL_FLOAT;
		case UE::ShaderDataType::Float3:	return GL_FLOAT;
		case UE::ShaderDataType::Float4:	return GL_FLOAT;
		case UE::ShaderDataType::Mat3:		return GL_FLOAT;
		case UE::ShaderDataType::Mat4:		return GL_FLOAT;
		case UE::ShaderDataType::Int:		return GL_INT;
		case UE::ShaderDataType::Int2:		return GL_INT;
		case UE::ShaderDataType::Int3:		return GL_INT;
		case UE::ShaderDataType::Int4:		return GL_INT;
		case UE::ShaderDataType::Bool:		return GL_BOOL;
		}

		UE_LOG_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_ID);
		vertexBuffer->Bind();
		
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}