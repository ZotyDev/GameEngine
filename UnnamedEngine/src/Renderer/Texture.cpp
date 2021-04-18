#include "Texture.h"

#include "logger/logger.h"

#include "Renderer/Renderer.h"
#include "Platform/Opengl/OpenGLTexture.h"

namespace UE 
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				Ref<OpenGLTexture2D> tempTexture2D = CreateRef<OpenGLTexture2D>();
				if (tempTexture2D->LoadFromSource(path))
				{
					UE_LOG_ERROR("Failed to create Texture2D!");
					return nullptr;
				}

				return tempTexture2D;
		}

		UE_LOG_ERROR("Unknown renderer!");
		return nullptr;
	}
}