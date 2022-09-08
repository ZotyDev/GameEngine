#include "uepch.h"
#include "Vulkan/VulkanDevice.h"

#include "Vulkan/VulkanContext.h"

#include "Core/Application.h"

namespace UE
{
	VulkanDevice::VulkanDevice()
	{}

	VulkanDevice::~VulkanDevice()
	{
		for (auto imageView : SwapChainImageViews)
		{
			vkDestroyImageView(Device, imageView, nullptr);
		}
		vkDestroySwapchainKHR(Device, SwapChain, nullptr);
		vkDestroyDevice(Device, nullptr);
		vkDestroySurfaceKHR(VulkanContext::Instance, Surface, nullptr);
	}

	struct QueueFamilyIndices
	{
		std::optional<UEUint32> GraphicsFamily;
		std::optional<UEUint32> PresentFamily;

		UEBool IsComplete()
		{
			return GraphicsFamily.has_value() && PresentFamily.has_value();
		}
	};

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) 
	{
		QueueFamilyIndices Indices;

		UEUint32 QueueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &QueueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &QueueFamilyCount, QueueFamilies.data());

		UEUint32 i = 0;
		for (const auto& queueFamily : QueueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				Indices.GraphicsFamily = i;
			}

			VkBool32 PresentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &PresentSupport);

			if (PresentSupport)
			{
				Indices.PresentFamily = i;
			}

			if (Indices.IsComplete())
			{
				break;
			}

			i++;
		}

		return Indices;
	}

	UEBool CheckDeviceExtensionSupport(VkPhysicalDevice	device)
	{
		UEUint32 ExtensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &ExtensionCount, nullptr);

		std::vector<VkExtensionProperties> AvaliableExtensions(ExtensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &ExtensionCount, AvaliableExtensions.data());

		std::set<UEString> RequiredExtensiosn(DeviceExtensions.begin(), DeviceExtensions.end());

		for (const auto& extension : AvaliableExtensions)
		{
			RequiredExtensiosn.erase(extension.extensionName);
		}

		return RequiredExtensiosn.empty();
	}

	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR Capabilities;
		std::vector<VkSurfaceFormatKHR> Formats;
		std::vector<VkPresentModeKHR> PresentModes;
	};

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		SwapChainSupportDetails Details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &Details.Capabilities);

		UEUint32 FormatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &FormatCount, nullptr);

		if (FormatCount != 0)
		{
			Details.Formats.resize(FormatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &FormatCount, Details.Formats.data());
		}

		UEUint32 PresentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &PresentModeCount, nullptr);

		if (PresentModeCount != 0)
		{
			Details.PresentModes.resize(PresentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &PresentModeCount, Details.PresentModes.data());
		}

		return Details;
	}

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& avaliableFormats)
	{
		for (const auto& avaliableFormat : avaliableFormats)
		{
			if (avaliableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && avaliableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return avaliableFormat;
			}
		}

		return avaliableFormats[0];
	}

	VkPresentModeKHR ChooseSwapSurfacePresentMode(const std::vector<VkPresentModeKHR>& avaliablePresentModes)
	{
		for (const auto& avaliablePresentMode : avaliablePresentModes)
		{
			if (avaliablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return avaliablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<UEUint32>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			UEUint32 Width = Application::s_Instance->m_Data->m_Window->GetWidth();
			UEUint32 Height = Application::s_Instance->m_Data->m_Window->GetHeight();

			VkExtent2D ActualExtent = { Width, Height };

			ActualExtent.width = std::clamp(ActualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.height);
			ActualExtent.height = std::clamp(ActualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return ActualExtent;
		}
	}

	UEBool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices Indices = FindQueueFamilies(device, surface);

		UEBool ExtensionSupported = CheckDeviceExtensionSupport(device);

		UEBool SwapChainAdequate = false;
		if (ExtensionSupported)
		{
			SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(device, surface);
			SwapChainAdequate = !SwapChainSupport.Formats.empty() && !SwapChainSupport.PresentModes.empty();
		}

		return Indices.IsComplete() && ExtensionSupported && SwapChainAdequate;
	}

	void VulkanDevice::Init()
	{
		// Create window surface
		if (glfwCreateWindowSurface(VulkanContext::Instance, (GLFWwindow*)Application::s_Instance->m_Data->m_Window->GetNativeWindow(), nullptr, &Surface) != VK_SUCCESS)
		{
			UE_CORE_ASSERT(FALSE, "Failed to create window surface");
			return;
		}

		// Get physical device
		UEUint32 DeviceCount = 0;
		vkEnumeratePhysicalDevices(VulkanContext::Instance, &DeviceCount, nullptr);
		if (DeviceCount == 0)
		{
			UE_CORE_ASSERT(false, "Failed to find GPUs with Vulkan support");
		}

		std::vector<VkPhysicalDevice> Devices(DeviceCount);
		vkEnumeratePhysicalDevices(VulkanContext::Instance, &DeviceCount, Devices.data());

		for (const auto& device : Devices)
		{
			if (IsDeviceSuitable(device, Surface))
			{
				PhysicalDevice = device;
				break;
			}
		}

		if (PhysicalDevice == VK_NULL_HANDLE)
		{
			UE_CORE_ASSERT(false, "Failed to find a suitable GPU");
		}

		// Create logical device
		QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice, Surface);

		std::vector<VkDeviceQueueCreateInfo> QueueCreateInfoList;
		std::set<UEUint32> UniqueQueueFamilies = { Indices.GraphicsFamily.value(), Indices.PresentFamily.value() };

		UEFloat QueuePriority = 1.0f;
		for (UEUint32 queueFamily : UniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo CurrentQueueCreateInfo{};
			CurrentQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			CurrentQueueCreateInfo.queueFamilyIndex = queueFamily;
			CurrentQueueCreateInfo.queueCount = 1;
			CurrentQueueCreateInfo.pQueuePriorities = &QueuePriority;
			QueueCreateInfoList.push_back(CurrentQueueCreateInfo);
		}

		VkPhysicalDeviceFeatures DeviceFeatures{};

		VkDeviceCreateInfo DeviceCreateInfo{};
		DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		DeviceCreateInfo.queueCreateInfoCount = static_cast<UEUint32>(QueueCreateInfoList.size());
		DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfoList.data();

		DeviceCreateInfo.pEnabledFeatures = &DeviceFeatures;

		DeviceCreateInfo.enabledExtensionCount = static_cast<UEUint32>(DeviceExtensions.size());
		DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

		if (EnableValidationLayers)
		{
			DeviceCreateInfo.enabledLayerCount = static_cast<UEUint32>(ValidationLayers.size());
			DeviceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else
		{
			DeviceCreateInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(PhysicalDevice, &DeviceCreateInfo, nullptr, &Device) != VK_SUCCESS)
		{
			UE_CORE_ASSERT(false, "Failed to create logical device");
		}

		// Get graphics queue
		vkGetDeviceQueue(Device, Indices.GraphicsFamily.value(), 0, &GraphicsQueue);

		// Get present queue
		vkGetDeviceQueue(Device, Indices.PresentFamily.value(), 0, &PresentQueue);

		// Creat swap chain
		SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(PhysicalDevice, Surface);

		VkSurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(SwapChainSupport.Formats);
		VkPresentModeKHR PresentMode = ChooseSwapSurfacePresentMode(SwapChainSupport.PresentModes);
		VkExtent2D Extent = ChooseSwapExtent(SwapChainSupport.Capabilities);

		UEUint32 ImageCount = SwapChainSupport.Capabilities.minImageCount + 1;
		
		if (SwapChainSupport.Capabilities.maxImageCount > 0 && ImageCount > SwapChainSupport.Capabilities.maxImageCount)
		{
			ImageCount = SwapChainSupport.Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR SwapChainCreateInfo{};
		SwapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		SwapChainCreateInfo.surface = Surface;
		SwapChainCreateInfo.minImageCount = ImageCount;
		SwapChainCreateInfo.imageFormat = SurfaceFormat.format;
		SwapChainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
		SwapChainCreateInfo.imageExtent = Extent;
		SwapChainCreateInfo.imageArrayLayers = 1;
		SwapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		UEUint32 QueueFamilyIndicesList[] = { Indices.GraphicsFamily.value(), Indices.PresentFamily.value() };
		
		if (Indices.GraphicsFamily != Indices.PresentFamily)
		{
			SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			SwapChainCreateInfo.queueFamilyIndexCount = 2;
			SwapChainCreateInfo.pQueueFamilyIndices = QueueFamilyIndicesList;
		}
		else
		{
			SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			SwapChainCreateInfo.queueFamilyIndexCount = 0;
			SwapChainCreateInfo.pQueueFamilyIndices = nullptr;
		}

		SwapChainCreateInfo.preTransform = SwapChainSupport.Capabilities.currentTransform;
		SwapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		SwapChainCreateInfo.presentMode = PresentMode;
		SwapChainCreateInfo.clipped = VK_TRUE;
		SwapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(Device, &SwapChainCreateInfo, nullptr, &SwapChain) != VK_SUCCESS)
		{
			UE_CORE_ASSERT(false, "Failed to create swap chain");
		}

		SwapChainFormat = SurfaceFormat.format;
		SwapChainExtent = Extent;

		// Get swap chain images
		vkGetSwapchainImagesKHR(Device, SwapChain, &ImageCount, nullptr);
		SwapChainImages.resize(ImageCount);
		vkGetSwapchainImagesKHR(Device, SwapChain, &ImageCount, SwapChainImages.data());

		// Create image views
		SwapChainImageViews.resize(SwapChainImages.size());

		for (UEUint32 i = 0; i < SwapChainImages.size(); i++)
		{
			VkImageViewCreateInfo CurrentImageViewCreateInfo{};
			CurrentImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			CurrentImageViewCreateInfo.image = SwapChainImages[i];
			CurrentImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			CurrentImageViewCreateInfo.format = SwapChainFormat;
			CurrentImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			CurrentImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			CurrentImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			CurrentImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			CurrentImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			CurrentImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
			CurrentImageViewCreateInfo.subresourceRange.levelCount = 1;
			CurrentImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
			CurrentImageViewCreateInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(Device, &CurrentImageViewCreateInfo, nullptr, &SwapChainImageViews[i]) != VK_SUCCESS)
			{
				UE_CORE_ASSERT(false, "Failed to create image views");
			}
		}

		// Create graphics pipeline
	}
}