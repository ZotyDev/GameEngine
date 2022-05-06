#include "uepch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace UE
{
	UEResult OpenGLTexture2D::LoadFromSource(const UEPath& path, TextureFlags flags)
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			UE_CORE_ERROR("Failed to load texture {0}: {1}", path, stbi_failure_reason());
			UE_CORE_ERROR("Using fallback texture to prevent crash");
			
			UE_CORE_ASSERT(LoadFromSource("assets/core/textures/fallback.png") == UEResult::Success, "Failed to load fallback texture");

			return UEResult::Error;
		}
		else
		{
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0;
			GLenum dataFormat = 0;
			switch (channels)
			{
			case 4:
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			case 3:
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			case 2:
				internalFormat = GL_RG16;
				dataFormat = GL_RG;
				break;
			case 1:
				internalFormat = GL_R16;
				dataFormat = GL_RED;
				break;
			default:
				UE_CORE_ERROR("Failed to load texture \"{0}\": unknown format with {1} channels", path, channels);
				return UEResult::Error;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
			glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);

			if (channels == 1)
			{
				GLint SwizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
				glTextureParameteriv(m_ID, GL_TEXTURE_SWIZZLE_RGBA, SwizzleMask);
			}
			else if (channels == 2)
			{
				GLint SwizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_GREEN };
				glTextureParameteriv(m_ID, GL_TEXTURE_SWIZZLE_RGBA, SwizzleMask);
			}
			
			if (flags | TextureFlags::FILTERING_NEAREST)
			{
				glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			else
			{
				glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

			if (flags | TextureFlags::CLAMP_TO_EDGE)
			{
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			else
			{
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_R, GL_REPEAT);
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}

			glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);

			return UEResult::Success;
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture2D::Bind(UEUint32 slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}
}