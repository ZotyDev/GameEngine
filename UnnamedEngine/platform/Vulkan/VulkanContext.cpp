#include "uepch.h"
#include "Vulkan/VulkanContext.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace UE
{
	#ifdef UE_DEBUG
	const bool EnableValidationLayers = true;
	#else
	const bool EnableValidationLayers = false;
	#endif

	const std::vector<const char*> ValidationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	bool CheckValidationLayerSupport()
	{
		uint32_t LayerCount;
		vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
		std::vector<VkLayerProperties> AvaliableLayers(LayerCount);
		vkEnumerateInstanceLayerProperties(&LayerCount, AvaliableLayers.data());

		for (const char* layerName : ValidationLayers)
		{
			bool LayerFound = false;

			for (const auto& layerProperties : AvaliableLayers)
			{
				if (std::strcmp(layerName, layerProperties.layerName) == 0)
				{
					LayerFound = true;
					break;
				}
			}

			if (!LayerFound)
			{
				return true;
			}
		}

		return true;
	}

	std::vector<const char*> GetRequiredExtensions()
	{
		uint32_t GlfwExtensionCount = 0;
		const char** GlfwExtensions;
		GlfwExtensions = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);
		std::vector<const char*> Extensions(GlfwExtensions, GlfwExtensions + GlfwExtensionCount);
		
		if (EnableValidationLayers)
		{
			Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return Extensions;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanMessageCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			switch (messageSeverity)
			{
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				UE_CORE_WARN("Vulkan validation layer: {0}", pCallbackData->pMessage);
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				UE_CORE_ERROR("Vulkan validation layer: {0}", pCallbackData->pMessage);
				break;
			default:
				UE_CORE_ERROR("Vulkan validation layer (Unknown severity): {0}", pCallbackData->pMessage);
				break;
			}
		}

		return VK_FALSE;
	}

	VkResult CreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto Function = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (Function != nullptr)
		{
			return Function(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator)
	{
		auto Function = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (Function != nullptr)
		{
			Function(instance, debugMessenger, pAllocator);
		}
	}

	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& CreateInfo)
	{
		CreateInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		CreateInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		CreateInfo.pfnUserCallback = VulkanMessageCallback;
		CreateInfo.pUserData = nullptr;
	} 

	void VulkanContext::SetupDebugMessenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT CreateInfo{};
		PopulateDebugMessengerCreateInfo(CreateInfo);

		if (CreateDebugUtilsMessengerEXT(*(VkInstance*)m_Instance, &CreateInfo, nullptr, (VkDebugUtilsMessengerEXT*)m_DebugMessenger) != VK_SUCCESS)
		{
			UE_CORE_ASSERT(false, "Failed to set up debug messenger");
		}
	}

	VulkanContext::VulkanContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle), m_Instance(VK_NULL_HANDLE), m_DebugMessenger(VK_NULL_HANDLE)
	{
		UE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	VulkanContext::~VulkanContext()
	{
		if (EnableValidationLayers)
		{
			DestroyDebugUtilsMessengerEXT(*(VkInstance*)m_Instance, *(VkDebugUtilsMessengerEXT*)m_DebugMessenger, nullptr);
		}

		vkDestroyInstance(*(VkInstance*)m_Instance, nullptr);
	}

	void VulkanContext::Init()
	{
		// Define the application info
		// Todo: get this information from somewhere and share it everywhere
		VkApplicationInfo AppInfo{};
		AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		AppInfo.pApplicationName = "VoxelGame";
		AppInfo.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		AppInfo.pEngineName = "Unnamed Engine";
		AppInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_2;

		// Define create info
		VkInstanceCreateInfo CreateInfo{};
		CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		CreateInfo.pApplicationInfo = &AppInfo;
		
		VkDebugUtilsMessengerCreateInfoEXT DebugCreateInfo{};

		if (EnableValidationLayers)
		{
			CreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = ValidationLayers.data();

			PopulateDebugMessengerCreateInfo(DebugCreateInfo);
			auto DebugFunctionPointer = (VkDebugUtilsMessengerCreateInfoEXT*)&DebugCreateInfo;
			CreateInfo.pNext = DebugFunctionPointer;
		}
		else
		{
			CreateInfo.enabledLayerCount = 0;

			CreateInfo.pNext = VK_NULL_HANDLE;
		}

		// Specify desired extensions
		auto Extensions = GetRequiredExtensions();
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
		CreateInfo.ppEnabledExtensionNames = Extensions.data();

		// Create vulkan instance
		VkInstance NewInstance;
		VkResult Result = vkCreateInstance(&CreateInfo, nullptr, &NewInstance);
		m_Instance = (void*)&NewInstance;

		if (Result != VK_SUCCESS)
		{
			UE_CORE_ERROR("Failed to create instance!");
		}

		// Extension handling
		uint32_t AvaliableExtensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &AvaliableExtensionCount, nullptr);
		std::vector<VkExtensionProperties> AvaliableExtensions(AvaliableExtensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &AvaliableExtensionCount, AvaliableExtensions.data());

		UE_CORE_INFO("Vulkan Info!");
		UE_CORE_INFO("	Required Extensions: {0}", CreateInfo.enabledExtensionCount);
		for (const auto& extension : Extensions)
		{
			bool ExtensionFound = false;

			for (const auto& avaliableExtension : AvaliableExtensions)
			{
				if (std::strcmp(extension, avaliableExtension.extensionName) == 0)
				{
					UE_CORE_INFO("		{0} - Found", extension);
					ExtensionFound = true;
					break;
				}
			}

			if (!ExtensionFound)
			{
				UE_CORE_ERROR("		{0} - Unavaliable", extension);
			}
		}

		// Validation layer handling
		if (EnableValidationLayers && !CheckValidationLayerSupport())
		{
			UE_CORE_ASSERT(false, "Validation layers requested, but not supported");
			SetupDebugMessenger();
		}

	}

	void VulkanContext::SwapBuffers()
	{

	}
}