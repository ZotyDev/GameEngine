#pragma once

// Todo:
// Prevent same names being used in different places
// i.e: registering "metallic" on both float and bool
//
// Change name from "*Value" to "*{Type}"

namespace UE
{
	class Material
	{
	public:
		Material();
		Material(Ref<Material> copy);
		
		~Material();

		UEResult RegisterValue(const std::string& name, bool value);
		UEResult RegisterValue(const std::string& name, int value);
		UEResult RegisterValue(const std::string& name, uint32_t value);
		UEResult RegisterValue(const std::string& name, float value);
		UEResult RemoveValue(const std::string& name);

		UEResult SetValue(const std::string& name, bool value);
		UEResult SetValue(const std::string& name, int value);
		UEResult SetValue(const std::string& name, uint32_t value);
		UEResult SetValue(const std::string& name, float value);

		UEResult ChangeValue(const std::string& name, int value);
		UEResult ChangeValue(const std::string& name, uint32_t value);
		UEResult ChangeValue(const std::string& name, float value);

		UEResult GetValue(const std::string& name, bool& value);
		UEResult GetValue(const std::string& name, int& value);
		UEResult GetValue(const std::string& name, uint32_t& value);
		UEResult GetValue(const std::string& name, float& value);
	private:
		std::unordered_map<std::string, bool> m_BoolValues;
		std::unordered_map<std::string, int> m_IntValues;
		std::unordered_map<std::string, uint32_t> m_Uint32Values;
		std::unordered_map<std::string, float> m_FloatValues;
	};

	class MaterialLibrary
	{
	public:
		UEResult Add(const std::string& name, Ref<Material> material);

		UEResult Get(const std::string& name, Ref<Material>& material);
	private:
		std::unordered_map<std::string, Ref<Material>> m_Materials;
	};
}