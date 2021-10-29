#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UE
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	private:
		void* m_Instance;
	private:
		void* m_DebugMessenger;
		void SetupDebugMessenger();
	};
}