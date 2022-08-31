#include "uepch.h"
#include "Core/ConfigManager.h"

#include "Script/Lune/LuneAPI.h"

#include "PlatformIndependenceLayer/FileSystem.h"
#include <fmt/format.h>

namespace UE
{
	UEString ConfingUpperFrameString =
		"local {0} = {{\n"
		"{1}\n"
		"}}\n"
		"\n"
		"return {0}";

	UEString ConfigContainerString =
		"[\"{0}\"] = {{\n"
		"{1}\n"
		"}},";

	void ReplaceAll(UEString& source, const UEString& from, const UEString& to)
	{
		UEString NewString;
		NewString.reserve(source.length());

		UEString::size_type LastPos = 0;
		UEString::size_type FindPos;

		while (UEString::npos != (FindPos = source.find(from, LastPos)))
		{
			NewString.append(source, LastPos, FindPos - LastPos);
			NewString += to;
			LastPos = FindPos + from.length();
		}

		NewString.append(source, LastPos, source.length() - LastPos);

		source.swap(NewString);
	}

	void InsertIndentation(UEString& string, UEUint32 indentation)
	{
		UEString IndentationString("\t", indentation);
		string.insert(0, IndentationString);
		ReplaceAll(string, "\n", "\n" + IndentationString);
	}

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
					configGroup->String.Register(ConfigName, ConfigValue);
					configGroup->m_OrderHelper.push_back(ConfigName);

					UE_CORE_INFO("{} : {}", ConfigName, ConfigValue);
					break;
				}
				case LUA_TBOOLEAN:
				{
					UEBool ConfigValue = lua_toboolean(L, -1);
					configGroup->Bool.Register(ConfigName, ConfigValue);
					configGroup->m_OrderHelper.push_back(ConfigName);

					UE_CORE_INFO("{} : {}", ConfigName, ConfigValue);
					break;
				}
				case LUA_TNUMBER:
				{
					UEDouble ConfigValue = lua_tonumber(L, -1);
					configGroup->Number.Register(ConfigName, ConfigValue);
					configGroup->m_OrderHelper.push_back(ConfigName);

					UE_CORE_INFO("{} : {}", ConfigName, ConfigValue);
					break;
				}
				case LUA_TFUNCTION:
				{
					UE_CORE_ERROR("Failed to load config \"{0}\": function is not a valid type", ConfigName);
					break;
				}
				case LUA_TTABLE:
				{
					UE_CORE_INFO(">{}:", ConfigName);

					Ref<ConfigGroup> NewConfigGroup = CreateRef<ConfigGroup>();
					configGroup->Groups.Register(ConfigName, NewConfigGroup);
					configGroup->m_OrderHelper.push_back(ConfigName);
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

	UEResult<> ConfigManager::LoadConfigFile(const UEPath& path, const UEPath& defaultPath)
	{
		LuneStack Lune;
		Lune.ExecuteFile(path.string());

		lua_State* L = Lune.L;

		ReadTable(L, m_ConfigGroup);

		return UEResult<>::Success;
	}

	UEResult<> ConfigManager::SaveConfigFile(const UEPath& path)
	{
		std::ofstream ConfigOutput;
		ConfigOutput.open(path);

		//UEString Containers = fmt::format(
		//	ConfigContainerString,
		//	"test",
		//	"\ttest"
		//	);
		//
		//InsertIndentation(Containers, 1);
		//
		//ConfigOutput << fmt::format(
		//	ConfingUpperFrameString,
		//	"test", Containers
		//);

		for (UEUint32 i = 0; i < m_ConfigGroup->m_OrderHelper.size(); i++)
		{
			ConfigOutput << m_ConfigGroup->m_OrderHelper[i] + "\n";
		}

		ConfigOutput.close();

		return UEResult<>::Success;
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

	UEResult<> SearchNumberConfig(UEDouble& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto groupResult = configGroup->Groups.Find(description[depth]);
		auto valueResult = configGroup->Number.Find(description[depth]);

		if (groupResult)
		{
			SearchNumberConfig(value, description, groupResult.Value, depth + 1);
		}
		else if (valueResult && (depth + 1) == description.size())
		{
			value = valueResult.Value;
		}
		else
		{
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> SearchStringConfig(UEString& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto groupResult = configGroup->Groups.Find(description[depth]);
		auto valueResult = configGroup->String.Find(description[depth]);

		if (groupResult)
		{
			SearchStringConfig(value, description, groupResult.Value, depth + 1);
		}
		else if (valueResult && (depth + 1) == description.size())
		{
			value = valueResult.Value;
		}
		else
		{
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> SearchBoolConfig(UEBool& value, const std::vector<UEString>& description, const Ref<ConfigGroup>& configGroup, UEUint32 depth = 0)
	{
		auto groupResult = configGroup->Groups.Find(description[depth]);
		auto valueResult = configGroup->Bool.Find(description[depth]);

		if (groupResult)
		{
			SearchBoolConfig(value, description, groupResult.Value, depth + 1);
		}
		else if (valueResult && (depth + 1) == description.size())
		{
			value = valueResult.Value;
		}
		else
		{
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> ConfigManager::GetNumberConfig(UEDouble& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchNumberConfig(value, description, m_ConfigGroup);
		if (!Result)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}

	UEResult<> ConfigManager::GetStringConfig(UEString& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchStringConfig(value, description, m_ConfigGroup);
		if (!Result)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}

	UEResult<> ConfigManager::GetBoolConfig(UEBool& value, const std::vector<UEString>& description)
	{
		UEResult Result = SearchBoolConfig(value, description, m_ConfigGroup);
		if (!Result)
		{
			UEString ConfigTotalDescription = ConcatConfigDescritpion(description);
			UE_CORE_ERROR("Could not find config \"{0}\": not a group or value\n Check if the description and type are correct", ConfigTotalDescription);
		}

		return Result;
	}
}