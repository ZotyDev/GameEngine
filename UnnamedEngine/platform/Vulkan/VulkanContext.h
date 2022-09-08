#pragma once

#include "Renderer/GraphicsContext.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace UE
{
	#ifdef UE_DEBUG
		const UEBool EnableValidationLayers = true;
	#else
		const UEBool EnableValidationLayers = false;
	#endif

	const std::vector<const char*> ValidationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	public:
		static VkInstance Instance;
	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		void SetupDebugMessenger();
	};
}