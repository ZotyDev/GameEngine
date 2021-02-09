#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "core.h"

#include "logger/logger.h"
#include "time/localTime.h"

namespace UE
{
	class UE_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

	private:

	};

	Application* CreateApplication();
}