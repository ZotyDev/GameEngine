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
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
		Ref<Texture2D> m_ImageIcon;
		Ref<Texture2D> m_LuaScriptIcon;
		Ref<Texture2D> m_FontIcon;
		Ref<Texture2D> m_TextIcon;
		Ref<Texture2D> m_AudioIcon;
		Ref<Texture2D> m_VertexShaderIcon;
		Ref<Texture2D> m_FragmentShaderIcon;
		Ref<Texture2D> m_MaterialDefinitionIcon;
		Ref<Texture2D> m_MaterialIcon;
	};
}