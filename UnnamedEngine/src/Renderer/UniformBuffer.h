#pragma once

namespace UE
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, UEUint32 size, UEUint32 offset = 0) = 0;

		static Ref<UniformBuffer> Create(UEUint32 size, UEUint32 binding);
	};
}