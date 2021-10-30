#include "uepch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLShader.h"
#endif

namespace UE
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL: 
			Ref<OpenGLShader> t_Shader = CreateRef<OpenGLShader>();
			if (t_Shader->LoadFromSource(filepath))
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}
			if (t_Shader->Compile())
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}

			return t_Shader;
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			Ref<OpenGLShader> t_Shader = CreateRef<OpenGLShader>();
			if (t_Shader->LoadFromSource(name, vertexSrc, fragmentSrc))
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}
			if (t_Shader->Compile())
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}

			return t_Shader;
		#endif
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string&name, const Ref<Shader>& shader)
	{
		if (Exists(name))
		{
			UE_CORE_ERROR("Shader already exists!");
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
			UE_CORE_ERROR("Shader not found!");
			return nullptr;
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}