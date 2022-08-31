#include "uepch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"

#if defined(UE_PLATFORM_OPENGL)
	#include "OpenGL/OpenGLShader.h"
#endif

namespace UE
{
	Ref<Shader> Shader::Create(const UEPath& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL: 
			Ref<OpenGLShader> t_Shader = CreateRef<OpenGLShader>();
			if (!t_Shader->LoadFromSource(path))
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}
			//if (t_Shader->Compile())
			//{
			//	UE_CORE_ERROR("Failed to create Shader!");
			//	return nullptr;
			//}

			return t_Shader;
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const UEString& name, const UEPath& vertexPath, const UEPath& fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			Ref<OpenGLShader> t_Shader = CreateRef<OpenGLShader>();
			if (!t_Shader->LoadFromSource(name, vertexPath, fragmentPath))
			{
				UE_CORE_ERROR("Failed to create Shader!");
				return nullptr;
			}
			//if (t_Shader->Compile())
			//{
			//	UE_CORE_ERROR("Failed to create Shader!");
			//	return nullptr;
			//}

			return t_Shader;
		#endif
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}

	std::unordered_map<UEString, Ref<Shader>> ShaderLibrary::m_Shaders = std::unordered_map<UEString, Ref<Shader>>();

	void ShaderLibrary::Add(const UEString&name, const Ref<Shader>& shader)
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

	Ref<Shader> ShaderLibrary::Load(const UEPath& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const UEString& name, const UEPath& path)
	{
		auto shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const UEString& name)
	{
		if (!Exists(name))
		{
			UE_CORE_ERROR("Shader not found!");
			return nullptr;
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const UEString& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}