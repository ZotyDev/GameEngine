#include "uepch.h"
#include "ProjectConfig.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include <toml.hpp>

namespace UE
{
	UEResult<> ProjectConfig::LoadConfigs()
	{
		// Check if file exist
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Could not read Projcts Config: could not find user data folder");
			return UEResult<>::Error;
		}

		// Load config file
		auto ConfigData = toml::parse<toml::preserve_comments>(UserDataFolder.string() + "/UnnamedEngine/ProjectsConfig.toml");

		// Create file if it does not exist

		// Create/Compare configs

		// Get configs
		// ProjectConfig
		auto& RecentProjects = toml::find(ConfigData, "RecentProjects");
		ProjectConfig::ProjectLocation = toml::find<UEString>(RecentProjects, "0");

		auto LastProject = toml::parse<toml::preserve_comments>(ProjectConfig::ProjectLocation.string() + "/ProjectConfig.toml");
		ProjectConfig::ProjectName = toml::find_or<UEString>(LastProject, "Name", "UnnamedProject");
		ProjectConfig::ProjectVersion = toml::find_or<UEString>(LastProject, "Version", "0.0.1α");

		return UEResult<>::Success;
	}

	UEString ProjectConfig::ProjectName = "UnnamedProject";
	UEPath ProjectConfig::ProjectLocation = "null";
	UEString ProjectConfig::ProjectVersion = "0.0.1α";

	UEPath ProjectConfig::AssetPath = "assets";
	UEPath ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;
}