#pragma once

#include "Core.h"

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