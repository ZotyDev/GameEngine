#include "uepch.h"
#include "Project/ProjectSerializer.h"

#include "EditorConfig.h"

#include "Project/Project.h"

namespace UE
{
	UEResult<> ProjectSerializer::Serialize(const UEPath& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Project" << YAML::Value << Project::Header::Name;
		out << YAML::Key << "Version" << YAML::Value << Project::Header::Version;
		out << YAML::EndMap;

		std::ofstream FileOutput(path.string() + "/Project.ue");
		FileOutput << out.c_str();

		return UEResult<>::Success;
	}

	UEResult<> ProjectSerializer::Deserialize(const UEPath& path)
	{
		YAML::Node Data;
		try
		{
			Data = YAML::LoadFile(path.string() + "/Project.ue");
		}
		catch (YAML::ParserException e)
		{
			UE_CORE_ERROR("Failed to load .ue file '{0}': {1}", path, e.what());
			return UEResult<>::Error;
		}

		if (!Data["Project"])
		{
			UE_CORE_ERROR("Failed to load .ue file '{0}': Empty file", path);
			return UEResult<>::Error;
		}

		Project::Header::Name = Data["Project"].as<UEString>();
		Project::Header::Version = Data["Version"].as<UEString>();
		Project::Header::Location = path;
		Project::Header::AssetPath = Project::Header::Location.string() + "/assets";
		Project::Header::CurrentDirectory = Project::Header::AssetPath;
		Project::Header::IsOpen = true;

		auto Begin = ProjectConfig::RecentProjects.begin();
		auto End = ProjectConfig::RecentProjects.end();
		if (ProjectConfig::RecentProjects.size() == 10)
		{
			ProjectConfig::RecentProjects.erase(Begin, Begin + (ProjectConfig::RecentProjects.size() - 10));
		}
		auto Search = std::find(Begin, End, path.string());
		if (Search != End)
		{
			ProjectConfig::RecentProjects.erase(Search);
		}
		ProjectConfig::RecentProjects.push_back(path.string());

		return UEResult<>::Success;
	}
}