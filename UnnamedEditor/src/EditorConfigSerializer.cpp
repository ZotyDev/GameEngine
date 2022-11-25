#include "uepch.h"
#include "EditorConfigSerializer.h"

#include "EditorConfig.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include "Project/Project.h"

namespace UE
{
	UEResult<> EditorConfigSerializer::Serialize()
	{
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to save editor configs: could not find user data folder");
			return UEResult<>::Error;
		}

		YAML::Emitter out;
		out << YAML::BeginMap; // Begin

		out << YAML::Key << "Projects" << YAML::BeginSeq;
		for (const auto& it : ProjectConfig::RecentProjects)
		{
			out << YAML::Value << it;
		}
		out << YAML::EndSeq; // Projects

		out << YAML::Key << "Config" << YAML::BeginMap;
		out << YAML::Key << "Fullscreen" << YAML::Value << PanelsConfig::Fullscreen;
		out << YAML::Key << "Padding" << YAML::Value << PanelsConfig::Padding;
		out << YAML::Key << "MaximizeOnPlay" << YAML::Value << PanelsConfig::MaximizeOnPlay;
		out << YAML::EndMap; // Config

		out << YAML::Key << "Active" << YAML::BeginMap;
		out << YAML::Key << "Viewport" << YAML::Value << ActivePanelsConfig::Viewport;
		out << YAML::Key << "ContentBrowser" << YAML::Value << ActivePanelsConfig::ContentBrowser;
		out << YAML::Key << "SceneHierarchy" << YAML::Value << ActivePanelsConfig::SceneHierarchy;
		out << YAML::Key << "Properties" << YAML::Value << ActivePanelsConfig::Properties;
		out << YAML::Key << "Profiler" << YAML::Value << ActivePanelsConfig::Profiler;
		out << YAML::Key << "NodeEditor" << YAML::Value << ActivePanelsConfig::NodeEditor;
		YAML::EndMap; // Active
		YAML::EndMap; // End

		std::ofstream FileOutput(UserDataFolder.string() + "/UnnamedEngine/EditorConfig.yaml");
		FileOutput << out.c_str();

		return UEResult<>::Success;
	}

	UEResult<> EditorConfigSerializer::Deserialize()
	{
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load editor configs: could not find user data folder");
			return UEResult<>::Error;
		}

		YAML::Node Data;
		try
		{
			Data = YAML::LoadFile(UserDataFolder.string() + "/UnnamedEngine/EditorConfig.yaml");
		}
		catch (YAML::ParserException e)
		{
			UE_CORE_ERROR("Failed to load editor configs: {0}", e.what());
			return UEResult<>::Error;
		}

		auto Projects = Data["Projects"];
		auto Config = Data["Config"];
		auto Active = Data["Active"];

		// Recent projects
		auto Begin = ProjectConfig::RecentProjects.begin();
		auto End = ProjectConfig::RecentProjects.end();
		for (const auto& it : Projects)
		{
			if (ProjectConfig::RecentProjects.size() == 10)
			{
				ProjectConfig::RecentProjects.erase(Begin, Begin + (ProjectConfig::RecentProjects.size() - 10));
			}
			auto Search = std::find(Begin, End, it.as<UEString>());
			if (Search != End)
			{
				ProjectConfig::RecentProjects.erase(Search);
			}
			if (FileSystem::DoesFileExists(it.as<UEString>() + "/Project.ue"))
			{
				ProjectConfig::RecentProjects.push_back(it.as<UEString>());
			}
		}

		// Panels config
		PanelsConfig::Fullscreen = Config["Fullscreen"].as<UEBool>(PanelsConfig::Fullscreen);
		PanelsConfig::Padding = Config["Padding"].as<UEBool>(PanelsConfig::Padding);
		PanelsConfig::MaximizeOnPlay = Config["MaximizeOnPlay"].as<UEBool>(PanelsConfig::MaximizeOnPlay);

		// Active panels config
		ActivePanelsConfig::Viewport = Active["Viewport"].as<UEBool>(ActivePanelsConfig::Viewport);
		ActivePanelsConfig::ContentBrowser = Active["ContentBrowser"].as<UEBool>(ActivePanelsConfig::ContentBrowser);
		ActivePanelsConfig::SceneHierarchy = Active["SceneHierarchy"].as<UEBool>(ActivePanelsConfig::SceneHierarchy);
		ActivePanelsConfig::Properties = Active["Properties"].as<UEBool>(ActivePanelsConfig::Properties);
		ActivePanelsConfig::Profiler = Active["Profiler"].as<UEBool>(ActivePanelsConfig::Profiler);
		ActivePanelsConfig::NodeEditor = Active["NodeEditor"].as<UEBool>(ActivePanelsConfig::NodeEditor);

		return UEResult<>::Error;
	}
}