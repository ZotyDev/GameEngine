#include "Application.h"

namespace UE
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		// Initialize GLFW
		if (!glfwInit())
		{
			UE_LOG_FATAL("Failed to initialize GLFW!");
			return;
		}

		LocalTime::Update();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
		if (!window)
		{
			UE_LOG_FATAL("Failed to create window!");
		}

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		UE_LOG_INFO(extensionCount, " supported extensions!");

		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		Logger::ShowLog("tatest.log");

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}