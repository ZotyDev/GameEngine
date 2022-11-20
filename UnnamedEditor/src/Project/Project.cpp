#include "uepch.h"
#include "Project/Project.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include <toml.hpp>

namespace UE
{
	UEString Project::Header::Name = "UnnamedProject";
	UEString Project::Header::Version = "0";
	UEPath Project::Header::Location = "null";
	UEPath Project::Header::AssetPath = "null";
	UEPath Project::Header::CurrentDirectory = "null";
	UEBool Project::Header::IsOpen = false;

	void SetRecentProject(const UEPath& path)
	{
		// Remove cringe backslashes from the path
		UEString NewPath = path.string();
		std::replace(NewPath.begin(), NewPath.end(), '\\', '/');

		// Create the config data
		const toml::value ConfigData{
			{"RecentProjects", {{"0", NewPath}}}
		};

		// Open the recent projects file
		UEPath UserDataFolder;
		FileSystem::GetUserDataFolder(UserDataFolder);
		std::ofstream ConfigFile(UserDataFolder.string() + "/UnnamedEngine/ProjectsConfig.toml", std::ios::binary);

		// Write to recents project file
		ConfigFile << toml::format(ConfigData, 0);
		ConfigFile.close();
	}

	UEResult<> Project::Create(const Project::Header& header)
	{
		// Check if there is already a folder with the same name inside
		UEPath ProjectFolder = header.Location.string() + "/" + header.Name;
		if (FileSystem::DoesFileExists(ProjectFolder))
		{
			return UEResult<>::Error;
		}

		// Create the main project folder
		FileSystem::MakeSureFolder(ProjectFolder);

		// Create the assets folder
		FileSystem::MakeSureFolder(ProjectFolder.string() + "/assets");

		// Set project header
		Header::Name = header.Name;
		Header::Version = header.Version;
		Header::Location = ProjectFolder;

		Header::AssetPath = Header::Location.string() + "/assets";
		Header::CurrentDirectory = Header::AssetPath;

		SetRecentProject(Header::Location);

		Header::IsOpen = true;

		return UEResult<>::Success;
	}
}