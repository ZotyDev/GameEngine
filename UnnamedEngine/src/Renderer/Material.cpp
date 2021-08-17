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

	UEResult Material::RegisterBool(const std::string& name, bool value)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register material value {0}: name already registered", name);
			return UEResult::Error;
		}

		m_BoolValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RegisterInt(const std::string& name, int value)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register material value {0}: name already registered", name);
			return UEResult::Error;
		}

		m_IntValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RegisterUint32(const std::string& name, uint32_t value)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register material value {0}: name already registered", name);
			return UEResult::Error;
		}

		m_Uint32Values.insert({ name, value });
		
		return UEResult::Success;
	}

	UEResult Material::RegisterFloat(const std::string& name, float value)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register material value {0}: name already registered", name);
			return UEResult::Error;
		}

		m_FloatValues.insert({ name, value });

		return UEResult::Success;
	}

	UEResult Material::RegisterShader(const std::string& name, Ref<Shader> shader)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register shader {0}: name already registered", name);
			return UEResult::Error;
		}

		m_Shaders.insert({ name, shader });

		return UEResult::Success;
	}

	UEResult Material::RegisterTexture(const std::string& name, Ref<Texture2D> texture)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Could not register texture {0}: name already registered", name);
			return UEResult::Error;
		}

		m_Textures.insert({ name, texture });

		return UEResult::Success;
	}

	UEResult Material::Remove(const std::string& name)
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
		else if (m_Shaders.find(name) != m_Shaders.end())
		{
			m_Shaders.erase(name);
			return UEResult::Success;
		}
		else if (m_Textures.find(name) != m_Textures.end())
		{
			m_Textures.erase(name);
			return UEResult::Success;
		}

		UE_CORE_ERROR("Could not remove material value {0}: not registered", name);
		return UEResult::Error;
	}

	UEResult Material::SetBool(const std::string& name, bool value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_BoolValues.find(name);
		if (it == m_BoolValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: type is not bool", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetInt(const std::string& name, int value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_IntValues.find(name);
		if (it == m_IntValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: type is not int", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetUint32(const std::string& name, uint32_t value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Uint32Values.find(name);
		if (it == m_Uint32Values.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: type is not uint32", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetFloat(const std::string& name, float value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_FloatValues.find(name);
		if (it == m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not set material value {0}: type is not float", name);
			return UEResult::Error;
		}

		it->second = value;

		return UEResult::Success;
	}

	UEResult Material::SetShader(const std::string& name, Ref<Shader> shader)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set shader {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Shaders.find(name);
		if (it == m_Shaders.end())
		{
			UE_CORE_ERROR("Could not set shader {0}: type is not shader", name);
			return UEResult::Error;
		}

		it->second = shader;

		return UEResult::Success;
	}

	UEResult Material::SetTexture(const std::string& name, Ref<Texture2D> texture)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not set texture {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Textures.find(name);
		if (it == m_Textures.end())
		{
			UE_CORE_ERROR("Could not set texture {0}: type is not texture", name);
			return UEResult::Error;
		}

		it->second = texture;

		return UEResult::Success;
	}

	UEResult Material::GetBool(const std::string& name, bool& value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_BoolValues.find(name);
		if (it == m_BoolValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: type is not bool", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetInt(const std::string& name, int& value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_IntValues.find(name);
		if (it == m_IntValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: type is not int", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetUint32(const std::string& name, uint32_t& value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Uint32Values.find(name);
		if (it == m_Uint32Values.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: type is not uint32", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetFloat(const std::string& name, float& value)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get material value {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_FloatValues.find(name);
		if (it == m_FloatValues.end())
		{
			UE_CORE_ERROR("Could not get material value {0}: type is not float", name);
			return UEResult::Error;
		}

		value = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetShader(const std::string& name, Ref<Shader>& shader)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get shader {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Shaders.find(name);
		if (it == m_Shaders.end())
		{
			UE_CORE_ERROR("Could not get shader {0}: type is not shader", name);
			return UEResult::Error;
		}

		shader = it->second;

		return UEResult::Success;
	}

	UEResult Material::GetTexture(const std::string& name, Ref<Texture2D>& texture)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Could not get texture {0}: not registered", name);
			return UEResult::Error;
		}

		auto it = m_Textures.find(name);
		if (it == m_Textures.end())
		{
			UE_CORE_ERROR("Could not get texture {0}: type is not texture", name);
			return UEResult::Error;
		}

		texture = it->second;

		return UEResult::Success;
	}

	bool Material::Exists(const std::string& name)
	{
		if (m_BoolValues.find(name) != m_BoolValues.end())
		{
			return true;
		}
		else if (m_IntValues.find(name) != m_IntValues.end())
		{
			return true;
		}
		else if (m_Uint32Values.find(name) != m_Uint32Values.end())
		{
			return true;
		}
		else if (m_FloatValues.find(name) != m_FloatValues.end())
		{
			return true;
		}
		else if (m_Shaders.find(name) != m_Shaders.end())
		{
			return true;
		}
		else if (m_Textures.find(name) != m_Textures.end())
		{
			return true;
		}

		return false;
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

	UEResult MaterialLibrary::CopyFrom(const std::string& name, Ref<Material>& material)
	{
		auto it = m_Materials.find(name);
		if (it == m_Materials.end())
		{
			UE_CORE_ERROR("Could not copy material {0}: not registered");
			return UEResult::Error;
		}

		material = CreateRef<Material>(it->second);

		return UEResult::Success;
	}

	UEResult MaterialLibrary::AddFromDefault(const std::string& name, Ref<Material>& material)
	{
		auto it = m_Materials.find("Default");
		if (it == m_Materials.end())
		{
			UE_CORE_ERROR("Could not copy from default: \"Default\" not registered");
			return UEResult::Error;
		}

		material = CreateRef<Material>(it->second);
		m_Materials.insert({ name, material });

		return UEResult::Success;
	}

	bool MaterialLibrary::Exists(const std::string& name)
	{
		return m_Materials.find(name) != m_Materials.end();
	}
}