#include "uepch.h"
#include "Vulkan/VulkanRendererAPI.h"

#include "Vulkan/VulkanContext.h"
#include "Vulkan/VulkanDevice.h"

namespace UE
{
	void VulkanRendererAPI::Init()
	{
		Device.Init();
	}

	void VulkanRendererAPI::SetViewport(UEUint32 x, UEUint32 y, UEUint32 width, UEUint32 height)
	{
		
	}

	void VulkanRendererAPI::GetViewport(UEUint32& width, UEUint32& height)
	{

	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{

	}

	void VulkanRendererAPI::Clear()
	{

	}

	void VulkanRendererAPI::ClearDepth()
	{

	}

	void VulkanRendererAPI::CullFront()
	{

	}

	void VulkanRendererAPI::CullBack()
	{

	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, UEUint32 indexCount)
	{

	}
}