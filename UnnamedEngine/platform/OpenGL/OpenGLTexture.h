#pragma once

#include "Renderer/Texture.h"
#include "glad/glad.h"

namespace UE
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D() = default;

		virtual UEResult LoadFromSource(const UEPath& path, TextureFlags flags = TextureFlags::NONE) override;
		virtual ~OpenGLTexture2D();

		virtual UEUint32 GetWidth() const override { return m_Width; };
		virtual UEUint32 GetHeight() const override { return m_Height; };
		virtual UEUint32 GetID() const override { return m_ID; };

		virtual void Bind(UEUint32 slot = 0) const override;
	private:
		UEUint32 m_Width;
		UEUint32 m_Height;
		UEUint32 m_ID;
		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}