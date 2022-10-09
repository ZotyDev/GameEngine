#include "uepch.h"
#include "Renderer/Material.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

#include "Renderer/Shader/ShaderHeaderConstructor.h"

namespace UE
{
	Material::Material()
	{}

	ShaderDataType StringToShaderDataType(UEString t)
	{
		if (t == "vec2")
		{
			return ShaderDataType::Vec2;
		}
		else if (t == "vec3")
		{
			return ShaderDataType::Vec3;
		}
		else if (t == "vec4")
		{
			return ShaderDataType::Vec4;
		}
		else if (t == "mat4")
		{
			return ShaderDataType::Mat4;
		}
		else if (t == "sampler2d")
		{
			return ShaderDataType::Sampler2D;
		}
		else
		{
			return ShaderDataType::Bool;
		}
	}

	ShaderHeaderConstructor::UseType StringToShaderUseType(UEString t)
	{
		if (t == "vertInput")
		{
			return ShaderHeaderConstructor::UseType::VertInput;
		}
		else if (t == "vertOutput")
		{
			return ShaderHeaderConstructor::UseType::VertOutput;
		}
		else if (t == "fragOutput")
		{
			return ShaderHeaderConstructor::UseType::FragOutput;
		}
		else if (t == "vertUniform")
		{
			return ShaderHeaderConstructor::UseType::VertUniform;
		}
		else if (t == "fragSampler")
		{
			return ShaderHeaderConstructor::UseType::FragSampler;
		}
		else
		{
			return ShaderHeaderConstructor::UseType::VertInput;
		}
	}

	Material::Material(const UEString& material)
	{
		// Load material
		YAML::Node Config = YAML::LoadFile("assets/materials/" + material + ".yaml");
		YAML::Node ShaderElements = Config["ShaderElements"];

		ShaderHeaderConstructor tShaderHeaderConstructor("assets/shaders/" + material);
		std::vector<ShaderHeaderConstructor::Element> tShaderElements;
		
		for (auto& it : ShaderElements)
		{
			UEString ShaderData = it.second["data"].as<UEString>();
			UEString ShaderUse = it.second["use"].as<UEString>();
			
			ShaderDataType tShaderDataType = StringToShaderDataType(ShaderData);
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