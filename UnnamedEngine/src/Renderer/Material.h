#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

// Todo:
// Remove the need for register and merge it inside set

namespace UE
{
	class Material
	{
	public:
		Material();
		Material(Ref<Material> copy);
		
		~Material();

		UEResult RegisterBool(const std::string& name, bool value);
		UEResult RegisterInt(const std::string& name, int value);
		UEResult RegisterUint32(const std::string& name, uint32_t value);
		UEResult RegisterFloat(const std::string& name, float value);
		
		UEResult RegisterShader(const std::string& name, Ref<Shader> shader);
		UEResult RegisterTexture(const std::string& name, Ref<Texture2D> texture);
		
		UEResult Remove(const std::string& name);

		UEResult SetBool(const std::string& name, bool value);
		UEResult SetInt(const std::string& name, int value);
		UEResult SetUint32(const std::string& name, uint32_t value);
		UEResult SetFloat(const std::string& name, float value);

		UEResult SetShader(const std::string& name, Ref<Shader> shader);
		UEResult SetTexture(const std::string& name, Ref<Texture2D> texture);

		UEResult GetBool(const std::string& name, bool& value);
		UEResult GetInt(const std::string& name, int& value);
		UEResult GetUint32(const std::string& name, uint32_t& value);
		UEResult GetFloat(const std::string& name, float& value);

		UEResult GetShader(const std::string& name, Ref<Shader>& shader);
		UEResult GetTexture(const std::string& name, Ref<Texture2D>& texture);

		bool Exists(const std::string& name);
	private:
		std::unordered_map<std::string, bool> m_BoolValues;
		std::unordered_map<std::string, int> m_IntValues;
		std::unordered_map<std::string, uint32_t> m_Uint32Values;
		std::unordered_map<std::string, float> m_FloatValues;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
	};

	class MaterialLibrary
	{
	public:
		UEResult Add(const std::string& name, Ref<Material> material);

		UEResult Get(const std::string& name, Ref<Material>& material);
		UEResult CopyFrom(const std::string& name, Ref<Material>& material);
		UEResult AddFromDefault(const std::string& name, Ref<Material>& material);
		
		bool Exists(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Material>> m_Materials;
	};
}