#include "uepch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace UE
{
	UEResult OpenGLTexture2D::LoadFromSource(const std::string& filepath)
	{
		int width;
		int height;
		int channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			UE_CORE_ERROR("Failed to load texture: ", stbi_failure_reason());
			return UEResult::Error;
		}

		if (data)
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
			default:
				UE_CORE_ERROR("Unknown format!");
				return UEResult::Error;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
			glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_ID, GL_TEXTURE_WRAP_R, GL_REPEAT);
			glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);

			return UEResult::Success;
		}
		return UEResult::Error;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}
}