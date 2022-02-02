#pragma once

#include "Renderer/IndexBuffer.h"

namespace UE
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(UEUint32* indices, UEUint32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual UEUint32 GetCount() const { return mCount; };

	private:
		unsigned int mID;
		UEUint32 mCount;
	};
}