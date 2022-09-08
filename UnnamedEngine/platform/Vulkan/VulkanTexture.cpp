#include "uepch.h"
#include "Vulkan/VulkanTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace UE
{
	UEResult<> VulkanTexture2D::LoadFromSource(const UEPath& path, TextureFlags flags)
	{
		return UEResult<>::Success;
	}

	VulkanTexture2D::~VulkanTexture2D()
	{

	}

	void VulkanTexture2D::Bind(UEUint32 slot) const
	{

	}
}