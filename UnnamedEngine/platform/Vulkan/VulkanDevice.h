#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace UE
{
	const std::vector<const char*> DeviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	class VulkanDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();

		void Init();

	private:
		VkSurfaceKHR Surface = VK_NULL_HANDLE;
		VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
		VkDevice Device = VK_NULL_HANDLE;
		VkQueue GraphicsQueue = VK_NULL_HANDLE;
		VkQueue PresentQueue = VK_NULL_HANDLE;
		VkSwapchainKHR SwapChain = VK_NULL_HANDLE;
		VkFormat SwapChainFormat;
		VkExtent2D SwapChainExtent;
		std::vector<VkImage> SwapChainImages;
		std::vector<VkImageView> SwapChainImageViews;
	};
}