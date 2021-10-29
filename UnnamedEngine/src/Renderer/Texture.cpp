#include "uepch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "OpenGL/OpenGLTexture.h"
#endif

namespace UE 
{
	Ref<Texture2D> Texture2D::Create()
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}