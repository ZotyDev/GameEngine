#pragma once

#include <UnnamedEngine.h>

namespace UE
{
	class MenuBarPanel
	{
	public:
		MenuBarPanel();

		void OnImGuiRender(Ref<Application::SharedData> data);
	};
}