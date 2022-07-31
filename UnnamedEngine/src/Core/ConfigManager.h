#pragma once

namespace UE
{
	struct ConfigGroup
	{
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

		UEResult GetNumberConfig(UEDouble& value, const std::vector<UEString>& description);
		UEResult GetStringConfig(UEString& value, const std::vector<UEString>& description);
		UEResult GetBoolConfig(UEBool& value, const std::vector<UEString>& description);
	private:
		Ref<ConfigGroup> m_ConfigGroup;
	};
}