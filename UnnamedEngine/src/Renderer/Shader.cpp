#include "Shader.h"

#include "Logger/Logger.h"

#include "Renderer/Renderer.h"
#include "Platform/Opengl/OpenGLShader.h"

namespace UE
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: 
				Ref<OpenGLShader> tempShader = CreateRef<OpenGLShader>();
				if (tempShader->LoadFromSource(filepath))
				{
					UE_LOG_ERROR("Failed to create Shader!");
					return nullptr;
				}
				if (tempShader->Compile())
				{
					UE_LOG_ERROR("Failed to create Shader!");
					return nullptr;
				}

				return tempShader;
		}

		UE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				Ref<OpenGLShader> tempShader = CreateRef<OpenGLShader>();
				if (tempShader->LoadFromSource(name, vertexSrc, fragmentSrc))
				{
					UE_LOG_ERROR("Failed to create Shader!");
					return nullptr;
				}
				if (tempShader->Compile())
				{
					UE_LOG_ERROR("Failed to create Shader!");
					return nullptr;
				}

				return tempShader;
		}

		UE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string&name, const Ref<Shader>& shader)
	{
		if (Exists(name))
		{
			UE_LOG_ERROR("Shader already exists!");
			return;
		}
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			UE_LOG_ERROR("Shader not found!");
			return nullptr;
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}