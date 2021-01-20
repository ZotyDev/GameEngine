#include "Application.h"

#include <GLFW/glfw3.h>

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
		TimeManager::Update();
		if (glfwInit())
		{
			LOG_FATAL("Not Working!");
		}


		Logger::ShowLog("latest.log");
		while (true)
		{
		}
	}
}