#pragma once

#include <filesystem>

#include "Renderer/Texture.h"

namespace UE
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::unordered_map<UEString, Ref<Texture2D>> m_Icons;
	};
}