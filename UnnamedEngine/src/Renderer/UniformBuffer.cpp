#include "uepch.h"
#include "Renderer/UniformBuffer.h"

#include "Renderer/Renderer.h"
#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLUniformBuffer.h"
#endif

namespace UE
{
	Ref<UniformBuffer> UniformBuffer::Create(UEUint32 size, UEUint32 binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLUniformBuffer>(size, binding);
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}