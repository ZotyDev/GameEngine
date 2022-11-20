#include "uepch.h"
#include "Renderer/Material.h"

#include "Renderer/Shader/ShaderHeaderConstructor.h"

namespace UE
{
	Material::Material()
	{}

	ShaderHeaderConstructor::UseType StringToShaderUseType(UEString t)
	{
		if (t == "vertInput") { return ShaderHeaderConstructor::UseType::VertInput; }
		else if (t == "vertOutput") { return ShaderHeaderConstructor::UseType::VertOutput; }
		else if (t == "fragInput") { return ShaderHeaderConstructor::UseType::FragInput; }
		else if (t == "fragOutput") { return ShaderHeaderConstructor::UseType::FragOutput; }
		else if (t == "vertUniform") { return ShaderHeaderConstructor::UseType::VertUniform; }
		else if (t == "fragUniform") { return ShaderHeaderConstructor::UseType::FragUniform; }
		else if (t == "fragSampler") { return ShaderHeaderConstructor::UseType::FragSampler; }
		else { return ShaderHeaderConstructor::UseType::Invalid; }
	}

	Material::Material(const UEString& material)
	{
		// Load material
		YAML::Node Config = YAML::LoadFile("assets/materials/" + material + ".mat");
		YAML::Node ShaderElements = Config["ShaderElements"];

		ShaderHeaderConstructor tShaderHeaderConstructor("assets/shaders/" + material);
		std::vector<ShaderHeaderConstructor::Element> tShaderElements;
		
		for (auto& it : ShaderElements)
		{
			UEString ShaderData = it.second["data"].as<UEString>();
			UEString ShaderUse = it.second["use"].as<UEString>();
			
			ShaderDataType tShaderDataType = ShaderHeaderConstructor::StringToDataType(ShaderData);
			ShaderHeaderConstructor::UseType tShaderUseType = StringToShaderUseType(ShaderUse);

			tShaderElements.push_back({
				it.first.as<UEString>(),
				tShaderDataType,
				tShaderUseType
				});
		}

		tShaderHeaderConstructor.SetElements(tShaderElements);

		UEString NewVertSource;
		UEString NewFragSource;

		tShaderHeaderConstructor.Construct(NewVertSource, NewFragSource);

		UE_CORE_WARN(NewVertSource);
		UE_CORE_WARN(NewFragSource);

		m_Shader = Shader::Create();
		m_Shader->Set(NewVertSource, NewFragSource);
	}

	Material::~Material()
	{}

	void Material::Bind()
	{
		m_Shader->Bind();
		for (UEUint32 i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind();
		}
	}

	void Material::SetShader(Ref<Shader> shader)
	{
		m_Shader = shader;
	}

	void Material::PushTexture(Ref<Texture> texture)
	{
		m_Textures.push_back(texture);
	}
}