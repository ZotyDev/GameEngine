#pragma once

namespace UE
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual UEUint32 GetCount() const = 0;
	
		static Ref<IndexBuffer> Create(UEUint32* indices, UEUint32 count);
	};
}