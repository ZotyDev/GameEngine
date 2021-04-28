#pragma once

#include "Renderer/Texture.h"
#include "glad/glad.h"

namespace UE
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D() = default;

		virtual int LoadFromSource(const std::string& filepath) override;
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetID() const override { return m_ID; };

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_ID;
		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}