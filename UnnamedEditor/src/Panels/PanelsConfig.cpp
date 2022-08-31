#include "uepch.h"
#include "Panels/PanelsConfig.h"

#include "Core/ConfigManager.h"
#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	UEResult<> PanelsConfig::LoadConfigs()
	{
		ConfigManager g;
		UEBool gb;
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load Editor Config: could not find user data folder");
			return UEResult<>::Error;
		}
		g.LoadConfigFile(UserDataFolder.string() + "/UnnamedEngine/EditorConfig.lua", "assets/configs/default/DEFAULT_EditorConfig.lua");
		g.SaveConfigFile("config.lua");

		// PanelsConfig
		if (g.GetBoolConfig(gb, { "PanelsConfig", "FullScreen" }))
		{
			PanelsConfig::OptFullscreen = gb;
		}
		if (g.GetBoolConfig(gb, { "PanelsConfig", "Padding" }))
		{
			PanelsConfig::OptPadding = gb;
		}
		if (g.GetBoolConfig(gb, { "PanelsConfig", "MaximizeOnPlay" }))
		{
			PanelsConfig::MaximizeOnPlay = gb;
		}

		// PanelsShowConfig
		if (g.GetBoolConfig(gb, { "ActivePanels", "Viewport" }))
		{
			PanelsShowConfig::ShowViewport = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "ContentBrowser" }))
		{
			PanelsShowConfig::ShowContentBrowser = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "SceneHierarchy" }))
		{
			PanelsShowConfig::ShowSceneHierarchy = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "Properties" }))
		{
			PanelsShowConfig::ShowProperties = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "Profiler" }))
		{
			PanelsShowConfig::ShowProfiler = gb;
		}

		return UEResult<>::Success;
	}

	UEBool PanelsConfig::OptFullscreen = true;
	UEBool PanelsConfig::OptPadding = false;

	UEBool PanelsConfig::MaximizeOnPlay = false;
	
	UEBool PanelsConfig::ProjectRunning = false;
	UEBool PanelsConfig::ProjectPaused = false;

	UEBool PanelsConfig::ViewportFocused = false;
	UEBool PanelsConfig::ViewportHovered = false;

	UEBool PanelsShowConfig::ShowViewport = true;
	UEBool PanelsShowConfig::ShowContentBrowser = true;
	UEBool PanelsShowConfig::ShowProperties = true;
	UEBool PanelsShowConfig::ShowSceneHierarchy = true;
	UEBool PanelsShowConfig::ShowProfiler = false;
}