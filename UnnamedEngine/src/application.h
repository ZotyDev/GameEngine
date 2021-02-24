#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Core.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Logger/Logger.h"
#include "Time/LocalTime.h"

namespace UE
{
	class UE_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void Update();
		void Render();

	private:

	};

	Application* CreateApplication();
}