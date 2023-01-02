#include "uepch.h"
#include "Project/Project.h"

#include "EditorConfig.h"

#include "Project/ProjectSerializer.h"
#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	UEString Project::Header::Name = "UnnamedProject";
	UEString Project::Header::Version = "0";
	UEPath Project::Header::Location = "null";
	UEPath Project::Header::AssetPath = "null";
	UEPath Project::Header::CurrentDirectory = "null";
	UEBool Project::Header::IsOpen = false;

	UEResult<> Project::Create(const Project::Header& header)
	{
		// Check if there is already a folder with the same name inside
		UEPath ProjectFolder = header.Location.string();
		if (header.Location.string().size() != 3)
		{
			ProjectFolder += "/";
		}
		ProjectFolder += header.Name;
		if (FileSystem::DoesFileExists(ProjectFolder))
		{
			return UEResult<>::Error;
		}

		// Create the main project folder
		FileSystem::MakeSureFolder(ProjectFolder);

		// Create the assets folder
		FileSystem::MakeSureFolder(ProjectFolder.string() + "/assets");

		// Create the cache folder
		FileSystem::MakeSureFolder(ProjectFolder.string() + "/.cache");

		// Set project header
		Header::Name = header.Name;
		Header::Version = header.Version;
		Header::Location = ProjectFolder;

		Header::AssetPath = Header::Location.string() + "/assets";
		Header::CurrentDirectory = Header::AssetPath;

		Header::IsOpen = true;

		ProjectSerializer::Serialize(ProjectFolder);

		auto Begin = ProjectConfig::RecentProjects.begin();
		auto End = ProjectConfig::RecentProjects.end();
		if (ProjectConfig::RecentProjects.size() == 10)
		{
			ProjectConfig::RecentProjects.erase(Begin, Begin + (ProjectConfig::RecentProjects.size() - 10));
		}
		auto Search = std::find(Begin, End, ProjectFolder.string());
		if (Search != End)
		{
			ProjectConfig::RecentProjects.erase(Search);
		}
		ProjectConfig::RecentProjects.push_back(ProjectFolder.string());

		return UEResult<>::Success;
	}
}