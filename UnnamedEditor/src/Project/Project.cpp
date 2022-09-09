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

		// Create the config file
		std::ofstream ConfigFile(ProjectFolder.string() + "/ProjectConfig.toml", std::ios::binary);

		const toml::value ConfigData{
			{"Name", header.Name},
			{"Version", header.Version}
		};

		ConfigFile << toml::format(ConfigData, 0);
		ConfigFile.close();

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

	UEResult<> Project::Read(const UEPath& path)
	{
		UEString ConfigFilePath = path.string() + "/ProjectConfig.toml";

		// Check if here is a config file inside the project folder
		if (!FileSystem::DoesFileExists(ConfigFilePath))
		{
			return UEResult<>::Error;
		}

		// Read configs
		auto ConfigData = toml::parse(ConfigFilePath);
		Header::Name = toml::find_or<UEString>(ConfigData, "Name", "UnnamedProject");
		Header::Version = toml::find_or<UEString>(ConfigData, "Version", "0.0.1a");
		Header::Location = path;

		Header::AssetPath = Header::Location.string() + "/assets";
		Header::CurrentDirectory = Header::AssetPath;

		SetRecentProject(Header::Location);

		Header::IsOpen = true;

		return UEResult<>::Success;
	}

	UEResult<> Project::ReadLatest()
	{
		// Get latest opened project
		UEPath UserDataFolder;
		FileSystem::GetUserDataFolder(UserDataFolder);
		if (!FileSystem::DoesFileExists(UserDataFolder.string() + "/UnnamedEngine/ProjectsConfig.toml"))
		{
			return UEResult<>::Error;
		}

		auto RecentProjects = toml::parse<toml::preserve_comments>(UserDataFolder.string() + "/UnnamedEngine/ProjectsConfig.toml");
		auto RecentProjectsHeader = toml::find(RecentProjects, "RecentProjects");
		UEPath Path = toml::find<UEString>(RecentProjectsHeader, "0");

		// Open the files
		UEString ConfigFilePath = Path.string() + "/ProjectConfig.toml";

		// Check if here is a config file inside the project folder
		if (!FileSystem::DoesFileExists(ConfigFilePath))
		{
			return UEResult<>::Error;
		}

		// Read configs
		auto ConfigData = toml::parse(ConfigFilePath);
		Header::Name = toml::find_or<UEString>(ConfigData, "Name", "UnnamedProject");
		Header::Version = toml::find_or<UEString>(ConfigData, "Version", "0.0.1a");
		Header::Location = Path;

		Header::AssetPath = Header::Location.string() + "/assets";
		Header::CurrentDirectory = Header::AssetPath;

		SetRecentProject(Header::Location);

		Header::IsOpen = true;

		return UEResult<>::Success;
	}
}