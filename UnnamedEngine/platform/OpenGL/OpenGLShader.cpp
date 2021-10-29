#include "uepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace UE
{
	int OpenGLShader::LoadFromSource(const std::string& filepath)
	{
		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// Open files
		vShaderFile.open(filepath + ".vert");
		if (!vShaderFile)
		{
			UE_CORE_ERROR("Failed to open ", filepath + ".vert");
			return -1;
		}

		fShaderFile.open(filepath + ".frag");
		if (!fShaderFile)
		{
			UE_CORE_ERROR("Failed to open ", filepath + ".frag");
			return -1;
		}

		// Read file's contents into streams
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		m_VertexCode = vShaderStream.str();
		m_FragmentCode = fShaderStream.str();

		return 0;
	}

	int OpenGLShader::LoadFromSource(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		m_Name = name;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// Open files
		vShaderFile.open(vertexSrc);
		if (!vShaderFile)
		{
			UE_CORE_ERROR("Failed to open ", vertexSrc);
			return -1;
		}

		fShaderFile.open(fragmentSrc);
		if (!fShaderFile)
		{
			UE_CORE_ERROR("Failed to open ", fragmentSrc);
			return -1;
		}

		// Read file's contents into streams
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		m_VertexCode = vShaderStream.str();
		m_FragmentCode = fShaderStream.str();

		return 0;
	}

	int OpenGLShader::Compile()
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
			return -1;
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
			return -1;
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
			return -1;
		}

		// Delete temporary shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return 0;
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

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}