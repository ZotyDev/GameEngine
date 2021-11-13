#pragma once

#include "Renderer/UniformBuffer.h"

namespace UE
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(UEUint32 size, UEUint32 binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* data, UEUint32 size, UEUint32 offset = 0) override;
	private:
		UEUint32 m_ID = 0;
	};
}