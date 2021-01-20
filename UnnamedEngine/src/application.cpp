#include "Application.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "time/timeManager.h"
#include "logger/logger.h"

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
			LOG_FATAL("Failed to initialize GLFW!");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window =glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		LOG_INFO(extensionCount, " supported extensions!");

		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		Logger::ShowLog("latest.log");

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}