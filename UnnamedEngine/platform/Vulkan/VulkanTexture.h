#pragma once

#include "Renderer/Texture.h"

namespace UE
{
	class VulkanTexture2D : public Texture2D
	{
	public:
		VulkanTexture2D() = default;

		virtual UEResult<> LoadFromSource(const UEPath& path, TextureFlags flags = TextureFlags::NONE) override;
		virtual ~VulkanTexture2D();

		virtual UEUint32 GetWidth() const override { return m_Width; };
		virtual UEUint32 GetHeight() const override { return m_Height; };
		virtual UEUint32 GetID() const override { return m_ID; };

		virtual void Bind(UEUint32 slot = 0) const override;
	private:
		UEUint32 m_Width;
		UEUint32 m_Height;
		UEUint32 m_ID;
		//GLenum m_InternalFormat;
		//GLenum m_DataFormat;
	};
}