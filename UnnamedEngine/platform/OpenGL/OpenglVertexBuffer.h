#pragma once

#include "Renderer/VertexBuffer.h"

namespace UE
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(UEUint32 size);
		OpenGLVertexBuffer(UEFloat* vertices, UEUint32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };

	private:
		UEUint32 m_ID;
		BufferLayout m_Layout;
	};
}