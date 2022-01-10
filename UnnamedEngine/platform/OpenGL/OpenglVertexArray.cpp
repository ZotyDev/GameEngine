#include "uepch.h"
#include "OpenglVertexArray.h"

#include <glad/glad.h>

namespace UE
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case UE::ShaderDataType::Bool:		return GL_BOOL;
		case UE::ShaderDataType::Int:		return GL_INT;
		case UE::ShaderDataType::Uint:		return GL_UNSIGNED_INT;
		case UE::ShaderDataType::Float:		return GL_FLOAT;
		case UE::ShaderDataType::Double:	return GL_DOUBLE;
		case UE::ShaderDataType::BVec2:		return GL_BOOL;
		case UE::ShaderDataType::BVec3:		return GL_BOOL;
		case UE::ShaderDataType::BVec4:		return GL_BOOL;
		case UE::ShaderDataType::IVec2:		return GL_INT;
		case UE::ShaderDataType::IVec3:		return GL_INT;
		case UE::ShaderDataType::IVec4:		return GL_INT;
		case UE::ShaderDataType::UVec2:		return GL_UNSIGNED_INT;
		case UE::ShaderDataType::UVec3:		return GL_UNSIGNED_INT;
		case UE::ShaderDataType::UVec4:		return GL_UNSIGNED_INT;
		case UE::ShaderDataType::Vec2:		return GL_FLOAT;
		case UE::ShaderDataType::Vec3:		return GL_FLOAT;
		case UE::ShaderDataType::Vec4:		return GL_FLOAT;
		case UE::ShaderDataType::DVec2:		return GL_DOUBLE;
		case UE::ShaderDataType::DVec3:		return GL_DOUBLE;
		case UE::ShaderDataType::DVec4:		return GL_DOUBLE;
		case UE::ShaderDataType::Mat2:		return GL_FLOAT;
		case UE::ShaderDataType::Mat3:		return GL_FLOAT;
		case UE::ShaderDataType::Mat4:		return GL_FLOAT;
		case UE::ShaderDataType::Mat2x2:	return GL_FLOAT;
		case UE::ShaderDataType::Mat2x3:	return GL_FLOAT;
		case UE::ShaderDataType::Mat2x4:	return GL_FLOAT;
		case UE::ShaderDataType::Mat3x2:	return GL_FLOAT;
		case UE::ShaderDataType::Mat3x3:	return GL_FLOAT;
		case UE::ShaderDataType::Mat3x4:	return GL_FLOAT;
		case UE::ShaderDataType::Mat4x2:	return GL_FLOAT;
		case UE::ShaderDataType::Mat4x3:	return GL_FLOAT;
		case UE::ShaderDataType::Mat4x4:	return GL_FLOAT;
		}

		UE_CORE_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
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
		
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Vec2:
			case ShaderDataType::Vec3:
			case ShaderDataType::Vec4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Double:
			case ShaderDataType::DVec2:
			case ShaderDataType::DVec3:
			case ShaderDataType::DVec4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribLPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::IVec2:
			case ShaderDataType::IVec3:
			case ShaderDataType::IVec4:
			case ShaderDataType::Uint:
			case ShaderDataType::UVec2:
			case ShaderDataType::UVec3:
			case ShaderDataType::UVec4:
			case ShaderDataType::Bool:
			case ShaderDataType::BVec2:
			case ShaderDataType::BVec3:
			case ShaderDataType::BVec4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat2:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			case ShaderDataType::Mat2x2:
			case ShaderDataType::Mat2x3:
			case ShaderDataType::Mat2x4:
			case ShaderDataType::Mat3x2:
			case ShaderDataType::Mat3x3:
			case ShaderDataType::Mat3x4:
			case ShaderDataType::Mat4x2:
			case ShaderDataType::Mat4x3:
			case ShaderDataType::Mat4x4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
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