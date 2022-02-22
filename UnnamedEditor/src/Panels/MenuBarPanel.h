#pragma once

#include "Core/Application.h"

namespace UE
{
	class MenuBarPanel
	{
	public:
		MenuBarPanel();

		void OnImGuiRender(Ref<Application::SharedData> data);
	};
}