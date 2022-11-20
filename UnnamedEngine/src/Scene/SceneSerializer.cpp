#include "uepch.h"
#include "Scene/SceneSerializer.h"

namespace UE
{
	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene) {}

	UEResult<> SceneSerializer::Serialize(const UEPath& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_Scene->m_Name;

		out << YAML::EndMap;

		std::ofstream FileOutput(path);
		FileOutput << out.c_str();

		return UEResult<>::Success;
	}

	UEResult<> SceneSerializer::Deserialize(const UEPath& path)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(path.string());
		}
		catch (YAML::ParserException e)
		{
			UE_CORE_ERROR("Failed to load .ue file '{0}': {1}", path, e.what());
			return UEResult<>::Error;
		}

		if (!data["Scene"])
		{
			UE_CORE_ERROR("Failed to load .ue file '{0}': Empty file", path);
			return UEResult<>::Error;
		}

		UEString SceneName = data["Scene"].as<UEString>();
		UE_CORE_TRACE("Deserializing scene '{0}'", SceneName);

		m_Scene->m_Name = SceneName;

		return UEResult<>::Success;
	}
}