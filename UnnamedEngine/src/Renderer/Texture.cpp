#include "uepch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/Opengl/OpenGLTexture.h"

namespace UE 
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			Ref<OpenGLTexture2D> tempTexture2D = CreateRef<OpenGLTexture2D>();
			if (tempTexture2D->LoadFromSource(path))
			{
				UE_CORE_ERROR("Failed to create Texture2D!");
				return nullptr;
			}
			return tempTexture2D;
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}