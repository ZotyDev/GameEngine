#pragma once

#include "Renderer/IndexBuffer.h"

namespace UE
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return mCount; };

	private:
		unsigned int mID;
		uint32_t mCount;
	};
}