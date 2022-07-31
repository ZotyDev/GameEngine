#include "uepch.h"
#include "ProjectConfig.h"

#include "Core/ConfigManager.h"
#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	UEResult ProjectConfig::LoadConfigs()
	{
		ConfigManager g;
		UEString gs;
		UEPath UserDataFolder;
		if (FileSystem::GetUserDataFolder(UserDataFolder) == UEResult::Error)
		{
			UE_CORE_ERROR("Could not read Projcts Config: could not find user data folder");
			return UEResult::Error;
		}
		g.LoadConfigFile(UserDataFolder.string() + "/UnnamedEngine/ProjectsConfig.lua", "assets/configs/default/DEFAULT_ProjectsConfig.lua");

		if (g.GetStringConfig(gs, { "LastOpened" }) == UEResult::Success)
		{
			ProjectConfig::AssetPath = UEPath(gs).append("assets");
			ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;

			ProjectConfig::ProjectLocation = gs;

			ConfigManager l;

			l.LoadConfigFile(ProjectConfig::ProjectLocation.append("ProjectConfig.lua"), "assets/configs/default/DEFAULT_ProjectConfig.lua");

			if (l.GetStringConfig(gs, { "Name" }) == UEResult::Success)
			{
				ProjectConfig::ProjectName = gs;
			}
			if (l.GetStringConfig(gs, { "Version" }) == UEResult::Success)
			{
				ProjectConfig::ProjectVersion = gs;
			}
		}

		return UEResult::Success;
	}

	UEString ProjectConfig::ProjectName = "UnnamedProject";
	UEPath ProjectConfig::ProjectLocation = "null";
	UEString ProjectConfig::ProjectVersion = "null";

	UEPath ProjectConfig::AssetPath = "assets";
	UEPath ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;
}