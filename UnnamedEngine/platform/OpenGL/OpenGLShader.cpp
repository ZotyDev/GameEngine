#include "uepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	UEResult OpenGLShader::LoadFromSource(const UEPath& path)
	{
		// Extract name from filepath
		auto lastSlash = path.string().find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.string().rfind('.');
		auto count = lastDot == std::string::npos ? path.string().size() - lastSlash : lastDot - lastSlash;
		UEString tName = path.string().substr(lastSlash, count);

		// Read shader source from files
		UEPath VertexPath = path;
		VertexPath += ".vert";

		UEPath FragmentPath = path;
		FragmentPath += ".frag";
		
		if (FileSystem::ReadToBuffer(VertexPath, m_VertexCode) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to load \"{0}\" Shader: could not read vertex source at {1}", tName, VertexPath);
			return UEResult::Error;
		}

		if (FileSystem::ReadToBuffer(FragmentPath, m_FragmentCode) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to load \"{0}\" Shader: could not read fragment source at {1}", tName, FragmentPath);
			return UEResult::Error;
		}

		m_Name = tName;

		return UEResult::Success;
	}

	UEResult OpenGLShader::LoadFromSource(const UEString& name, const UEPath& vertexPath, const UEPath& fragmentPath)
	{

		// Read shader source from files
		if (FileSystem::ReadToBuffer(vertexPath, m_VertexCode) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to load \"{0}\" Shader: could not read vertex source at {1}", name, vertexPath);
			return UEResult::Error;
		}

		if (FileSystem::ReadToBuffer(fragmentPath, m_FragmentCode) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to load \"{0}\" Shader: could not read fragment source at {1}", name, fragmentPath);
			return UEResult::Error;
		}

		m_Name = name;

		return UEResult::Success;
	}

	UEResult OpenGLShader::Compile()
	{
		unsigned int vertex;
		unsigned int fragment;
		int success;
		char infoLog[512];

		// Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* tmp_VertexCode = m_VertexCode.c_str();
		glShaderSource(vertex, 1, &tmp_VertexCode, NULL);
		glCompileShader(vertex);

		// Check for errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			UE_CORE_ERROR("Failed to compile Vertex Shader:\n {0}", infoLog);
			return UEResult::Error;
		}

		// Fragmnet shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char* tmp_FragmentCode = m_FragmentCode.c_str();
		glShaderSource(fragment, 1, &tmp_FragmentCode, NULL);
		glCompileShader(fragment);

		// Check for errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			UE_CORE_ERROR("Failed to compile Fragment Shader:\n {0}", infoLog);
			std::cout << infoLog << "\n";
			return UEResult::Error;
		}

		// Shader Program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		// Check for errors
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			UE_CORE_ERROR("Failed to link Shader Program:\n {0}", infoLog);
			std::cout << infoLog << "\n";
			return UEResult::Error;
		}

		// Delete temporary shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return UEResult::Success;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::Set(const UEString& vertSource, const UEString& fragSource)
	{
		m_VertexCode = vertSource;
		m_FragmentCode = fragSource;
		Compile();
	}

	UEInt32 OpenGLShader::GetUniformLocation(const UEString& name)
	{
		return glGetUniformLocation(m_ID, name.c_str());
	}

	void OpenGLShader::SetBool(const UEString& name, UEBool value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetInt(const UEString& name, UEInt32 value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUint(const UEString& name, UEUint32 value)
	{
		glUniform1ui(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat(const UEString& name, UEFloat value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetDouble(const UEString& name, UEDouble value)
	{
		glUniform1d(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetBVec2(const UEString& name, const glm::bvec2& value)
	{
		glUniform2i(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetBVec3(const UEString& name, const glm::bvec3& value)
	{
		glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetBVec4(const UEString& name, const glm::bvec4& value)
	{
		glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetIVec2(const UEString& name, const glm::ivec2& value)
	{
		glUniform2i(GetUniformLocation(name.c_str()), value.x, value.y);
	}

	void OpenGLShader::SetIVec3(const UEString& name, const glm::ivec3& value)
	{
		glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetIVec4(const UEString& name, const glm::ivec4& value)
	{
		glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUVec2(const UEString& name, const glm::uvec2& value)
	{
		glUniform2ui(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetUVec3(const UEString& name, const glm::uvec3& value)
	{
		glUniform3ui(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetUVec4(const UEString& name, const glm::uvec4& value)
	{
		glUniform4ui(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetVec2(const UEString& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetVec3(const UEString& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const UEString& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetDVec2(const UEString& name, const glm::dvec2& value)
	{
		glUniform2d(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetDVec3(const UEString& name, const glm::dvec3& value)
	{
		glUniform3d(GetUniformLocation(name.c_str()), value.x, value.y, value.z);
	}

	void OpenGLShader::SetDVec4(const UEString& name, const glm::dvec4& value)
	{
		glUniform4d(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat2(const UEString& name, const glm::mat2& value)
	{
		SetMat2x2(name, value);
	}

	void OpenGLShader::SetMat3(const UEString& name, const glm::mat3& value)
	{
		SetMat3x3(name, value);
	}

	void OpenGLShader::SetMat4(const UEString& name, const glm::mat4& value)
	{
		SetMat4x4(name, value);
	}

	void OpenGLShader::SetMat2x2(const UEString& name, const glm::mat2x2& value)
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat2x3(const UEString& name, const glm::mat2x3& value)
	{
		glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat2x4(const UEString& name, const glm::mat2x4& value)
	{
		glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3x2(const UEString& name, const glm::mat3x2& value)
	{
		glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3x3(const UEString& name, const glm::mat3x3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3x4(const UEString& name, const glm::mat3x4& value)
	{
		glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4x2(const UEString& name, const glm::mat4x2& value)
	{
		glUniformMatrix4x2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4x3(const UEString& name, const glm::mat4x3& value)
	{
		glUniformMatrix4x3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4x4(const UEString& name, const glm::mat4x4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
}