#include "uepch.h"
#include "Core/ConfigManager.h"

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	void ReadTable(lua_State* L, Ref<ConfigGroup> configGroup)
	{
		lua_pushnil(L);
		while (lua_next(L, -2) != 0)
		{
			// Push a copy of the key into the stack
			// Why?
			// "If the value is a number, then lua_tostring() also changes the actual value in the
			// stach to a string. (This change confuses lua_next() when lua_tostring() is applied
			// to keys during table traversal.)"
			lua_pushvalue(L, -2);
			UEString ConfigName = lua_tostring(L, -1);
			// Remove the copy of the key from the stack
			lua_remove(L, -1);

			// Store the config based on type
			UEUint32 Type = lua_type(L, -1);
			switch (Type)
			{
			case LUA_TNIL:
			{
				UE_CORE_ERROR("Failed to load config \"{0}\": nil is not a valid type", ConfigName);
				break;
			}
			case LUA_TSTRING:
			{
				UEString ConfigValue = lua_tostring(L, -1);
				configGroup->StringConfigs.insert({ ConfigName, ConfigValue });

				//UE_CORE_INFO("{0} = {1}", ConfigName, ConfigValue);
				break;
			}
			case LUA_TBOOLEAN:
			{
				UEBool ConfigValue = lua_toboolean(L, -1);
				configGroup->BoolConfigs.insert({ ConfigName, ConfigValue });

				//UE_CORE_INFO("{0} = {1}", ConfigName, ConfigValue);
				break;
			}
			case LUA_TNUMBER:
			{
				UEDouble ConfigValue = lua_tonumber(L, -1);
				configGroup->NumberConfigs.insert({ ConfigName, ConfigValue });

				//UE_CORE_INFO("{0} = {1}", ConfigName, ConfigValue);
				break;
			}
			case LUA_TFUNCTION:
			{
				UE_CORE_ERROR("Failed to load config \"{0}\": function is not a valid type", ConfigName);
				break;
			}
			case LUA_TTABLE:
			{
				//UE_CORE_INFO("{0}:", ConfigName);

				Ref<ConfigGroup> NewConfigGroup = CreateRef<ConfigGroup>();
				configGroup->MyGroups.insert({ ConfigName, NewConfigGroup });
				ReadTable(L, NewConfigGroup);
				break;
			}
			default:
			{
				UE_CORE_ERROR("Failed to load config \"{0}\": invalid type", ConfigName);
				break;
			}
			}

			lua_pop(L, 1);
		}
	}

	ConfigManager::ConfigManager()
	{
		m_ConfigGroup = CreateRef<ConfigGroup>();
	}

	UEResult ConfigManager::LoadConfigFile(const UEPath& path, const UEPath& defaultPath)
	{
		LuneStack Lune;
		Lune.ExecuteFile(path.string());

		lua_State* L = Lune.L;

		ReadTable(L, m_ConfigGroup);

		return UEResult::Success;
	}

	UEString ConcatConfigDescritpion(const std::vector<UEString>& description)
	{
		UEString ConfigTotalDescription = "";
		for (auto& it : description)
		{
			ConfigTotalDescription += it + " ";
		}

		return ConfigTotalDescription;
	}

	UEResult SearchNumberConfig(UEDouble& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto group_it = configGroup->MyGroups.find(description[depth]);
		auto group_end = configGroup->MyGroups.end();
		auto value_it = configGroup->NumberConfigs.find(description[depth]);
		auto value_end = configGroup->NumberConfigs.end();
		if (group_it != group_end)
		{
			SearchNumberConfig(value, description, group_it->second, depth + 1);
		}
		else if (value_it != value_end && (depth + 1) == description.size())
		{
			value = value_it->second;
		}
		else
		{
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult SearchStringConfig(UEString& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto group_it = configGroup->MyGroups.find(description[depth]);
		auto group_end = configGroup->MyGroups.end();
		auto value_it = configGroup->StringConfigs.find(description[depth]);
		auto value_end = configGroup->StringConfigs.end();
		if (group_it != group_end)
		{
			SearchStringConfig(value, description, group_it->second, depth + 1);
		}
		else if (value_it != value_end && (depth + 1) == description.size())
		{
			value = value_it->second;
		}
		else
		{
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult SearchBoolConfig(UEBool& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto group_it = configGroup->MyGroups.find(description[depth]);
		auto group_end = configGroup->MyGroups.end();
		auto value_it = configGroup->BoolConfigs.find(description[depth]);
		auto value_end = configGroup->BoolConfigs.end();
		if (group_it != group_end)
		{
			SearchBoolConfig(value, description, group_it->second, depth + 1);
		}
		else if (value_it != value_end && (depth + 1) == description.size())
		{
			value = value_it->second;
		}
		else
		{
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult ConfigManager::GetNumberConfig(UEDouble& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchNumberConfig(value, description, m_ConfigGroup);
		if (Result == UEResult::Error)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}

	UEResult ConfigManager::GetStringConfig(UEString& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchStringConfig(value, description, m_ConfigGroup);
		if (Result == UEResult::Error)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}

	UEResult ConfigManager::GetBoolConfig(UEBool& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchBoolConfig(value, description, m_ConfigGroup);
		if (Result == UEResult::Error)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}
}