#pragma once

namespace UE
{
	template<typename T>
	class ConfigContainer
	{
	public:
		UEResult Register(const UEString& name, const T& element)
		{
			// Check if config is already registered
			auto it = m_Configs.find(name);
			if (it != m_Configs.end())
			{
				UE_CORE_ERROR("Failed to register config: name already registered in this container");
				return UEResult::Error;
			}

			// Register config
			m_Configs.insert(std::pair<UEString, T>(name, element));
			m_OrderHelper.push_back(name);
			return UEResult::Success;
		}

	public:
		std::unordered_map<UEString, T> m_Configs;
		std::vector<UEString> m_OrderHelper;
	};

	struct ConfigGroup
	{
		ConfigContainer<UEDouble> Number;
		ConfigContainer<UEString> String;
		ConfigContainer<UEBool> Bool;

		ConfigContainer<Ref<ConfigGroup>> Groups;

		std::unordered_map<UEString, UEDouble> NumberConfigs{};
		std::unordered_map<UEString, UEString> StringConfigs{};
		std::unordered_map<UEString, UEBool> BoolConfigs{};

		std::unordered_map<UEString, Ref<ConfigGroup>> MyGroups;
	};

	class ConfigManager
	{
	public:
		ConfigManager();

		UEResult LoadConfigFile(const UEPath& path, const UEPath& defaultPath);
		//UEResult SaveConfigFile(const UEPath& path);

		UEResult GetNumberConfig(UEDouble& value, const std::vector<UEString>& description);
		UEResult GetStringConfig(UEString& value, const std::vector<UEString>& description);
		UEResult GetBoolConfig(UEBool& value, const std::vector<UEString>& description);
	private:
		Ref<ConfigGroup> m_ConfigGroup;
	};
}