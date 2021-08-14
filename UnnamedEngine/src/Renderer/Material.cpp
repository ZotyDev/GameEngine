#include "uepch.h"
#include "Renderer/Material.h"

namespace UE
{
	Material::Material()
	{}

	Material::Material(Ref<Material> copy)
		: m_BoolValues(copy->m_BoolValues), m_IntValues(copy->m_IntValues), m_FloatValues(copy->m_FloatValues)
	{}

	Material::~Material()
	{}

	UEResult Material::RegisterValue(const std::string& name, bool value)
	{
		if (m_BoolValues.find(name) != m_BoolValues.end())
		{
			UE_CORE_ERROR("Could not register material value {0}: already registered", name);
			return UEResult::Error;
		}

		m_BoolValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RegisterValue(const std::string& name, int value)
	{
		if (m_IntValues.find(name) != m_IntValues.end())
		{
			UE_CORE_ERROR("Could not register material value {0}: already registered", name);
			return UEResult::Error;
		}

		m_IntValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RegisterValue(const std::string& name, uint32_t value)
	{
		if (m_Uint32Values.find(name) != m_Uint32Values.end())
		{
			UE_CORE_ERROR("Could not register material value {0}: already registered", name);
			return UEResult::Error;
		}

		m_Uint32Values.insert({ name, value });
		
		return UEResult::Success;
	}

	UEResult Material::RegisterValue(const std::string& name, float value)
	{
		if (m_FloatValues.find(name) != m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not register material value {0}: already registered", name);
			return UEResult::Error;
		}

		m_FloatValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RemoveValue(const std::string& name)
	{
		if (m_BoolValues.find(name) != m_BoolValues.end())
		{
			m_BoolValues.erase(name);
			return UEResult::Success;
		}
		else if (m_IntValues.find(name) != m_IntValues.end())
		{
			m_IntValues.erase(name);
			return UEResult::Success;
		}
		else if (m_Uint32Values.find(name) != m_Uint32Values.end())
		{
			m_Uint32Values.erase(name);
			return UEResult::Success;
		}
		else if (m_FloatValues.find(name) != m_FloatValues.end())
		{
			m_FloatValues.erase(name);
			return UEResult::Success;
		}

		UE_CORE_ERROR("Could not remove material value {0}: not registered", name);
		return UEResult::Error;
	}

	UEResult Material::SetValue(const std::string& name, bool value)
	{
		auto it = m_BoolValues.find(name);
		if (it == m_BoolValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetValue(const std::string& name, int value)
	{
		auto it = m_IntValues.find(name);
		if (it == m_IntValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetValue(const std::string& name, uint32_t value)
	{
		auto it = m_Uint32Values.find(name);
		if (it == m_Uint32Values.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetValue(const std::string& name, float value)
	{
		auto it = m_FloatValues.find(name);
		if (it == m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::ChangeValue(const std::string& name, int value)
	{
		auto it = m_IntValues.find(name);
		if (it == m_IntValues.end())
		{
			UE_CORE_ERROR("Could not cahnge material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second += value;

		return UEResult::Success;
	}

	UEResult Material::ChangeValue(const std::string& name, uint32_t value)
	{
		auto it = m_Uint32Values.find(name);
		if (it == m_Uint32Values.end())
		{
			UE_CORE_ERROR("Couuld not change material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second += value;

		return UEResult::Success;
	}

	UEResult Material::ChangeValue(const std::string& name, float value)
	{
		auto it = m_FloatValues.find(name);
		if (it == m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not change material value {0}: not registered", name);
			return UEResult::Error;
		}

		it->second += value;

		return UEResult::Success;
	}

	UEResult Material::GetValue(const std::string& name, bool& value)
	{
		auto it = m_BoolValues.find(name);
		if (it == m_BoolValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetValue(const std::string& name, int& value)
	{
		auto it = m_IntValues.find(name);
		if (it == m_IntValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetValue(const std::string& name, uint32_t& value)
	{
		auto it = m_Uint32Values.find(name);
		if (it == m_Uint32Values.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetValue(const std::string& name, float& value)
	{
		auto it = m_FloatValues.find(name);
		if (it == m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult MaterialLibrary::Add(const std::string& name, Ref<Material> material)
	{
		auto it = m_Materials.find(name);
		if (it != m_Materials.end())
		{
			UE_CORE_ERROR("Could not add material {0}: already registered");
			return UEResult::Error;
		}

		m_Materials.insert({ name, material });

		return UEResult::Success;
	}

	UEResult MaterialLibrary::Get(const std::string& name, Ref<Material>& material)
	{
		auto it = m_Materials.find(name);
		if (it == m_Materials.end())
		{
			UE_CORE_ERROR("Could not get material {0}: not registered");
			return UEResult::Error;
		}

		material = it->second;

		return UEResult::Success;
	}
}