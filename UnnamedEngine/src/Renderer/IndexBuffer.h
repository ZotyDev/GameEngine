#pragma once

namespace UE
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		virtual ~IndexBuffer() {};
	};
}