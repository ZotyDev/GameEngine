#include "uepch.h"
#include "Panels/PanelsConfig.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include <toml.hpp>

namespace UE
{
	UEResult<> PanelsConfig::LoadConfigs()
	{
		// Check if file exist
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load Editor Config: could not find user data folder");
			return UEResult<>::Error;
		}

		// Load config file
		auto ConfigData = toml::parse<toml::preserve_comments>(UserDataFolder.string() + "/UnnamedEngine/EditorConfig.toml");

		// Create file if it does not exist

		// Create/Compare configs

		// Get configs
		// PanelsConfig
		auto& TomlPanelsConfig = toml::find(ConfigData, "PanelsConfig");
		PanelsConfig::Fullscreen = toml::find_or<UEBool>(TomlPanelsConfig, "Fullscreen", true);
		PanelsConfig::Padding = toml::find_or<UEBool>(TomlPanelsConfig, "Padding", false);
		PanelsConfig::MaximizeOnPlay = toml::find_or<UEBool>(TomlPanelsConfig, "MaximizeOnPlay", false);

		// PanelsShowConfig
		auto& TomlActivePanelsConfig = toml::find(ConfigData, "ActivePanels");
		ActivePanelsConfig::Viewport = toml::find_or<UEBool>(TomlActivePanelsConfig, "Viewport", true);
		ActivePanelsConfig::ContentBrowser = toml::find_or<UEBool>(TomlActivePanelsConfig, "ContentBrowser", true);
		ActivePanelsConfig::SceneHierarchy = toml::find_or<UEBool>(TomlActivePanelsConfig, "Properties", true);
		ActivePanelsConfig::Profiler = toml::find_or<UEBool>(TomlActivePanelsConfig, "Profiler", true);

		return UEResult<>::Success;
	}

	UEBool PanelsConfig::Fullscreen = true;
	UEBool PanelsConfig::Padding = false;

	UEBool PanelsConfig::MaximizeOnPlay = false;
	
	UEBool PanelsConfig::ProjectRunning = false;
	UEBool PanelsConfig::ProjectPaused = false;

	UEBool PanelsConfig::ViewportFocused = false;
	UEBool PanelsConfig::ViewportHovered = false;

	UEBool ActivePanelsConfig::Viewport = true;
	UEBool ActivePanelsConfig::ContentBrowser = true;
	UEBool ActivePanelsConfig::Properties = true;
	UEBool ActivePanelsConfig::SceneHierarchy = true;
	UEBool ActivePanelsConfig::Profiler = false;
}