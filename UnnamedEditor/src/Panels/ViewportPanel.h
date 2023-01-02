#pragma once

#include "Core/Application.h"
#include "Renderer/Framebuffer.h"

#include <glm/glm.hpp>

namespace UE
{
	class ViewportPanel
	{
	public:
		ViewportPanel();

		void OnImGuiRender(Ref<Application::SharedData> data, glm::vec2* viewportBounds, glm::vec2* viewportSize, Ref<Framebuffer> framebuffer);
	};
}