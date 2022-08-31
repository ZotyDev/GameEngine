#pragma once

#include "Renderer/Shader.h"

namespace UE
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader() = default;

		virtual UEResult<> LoadFromSource(const UEPath& path) override;
		virtual UEResult<> LoadFromSource(const UEString& name, const UEPath& vertexPath, const UEPath& fragmentPath) override;

		virtual UEResult<> Compile() override;

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Set(const UEString& vertSource, const UEString& fragSource) override;

		virtual void SetBool(const UEString& name, UEBool value) override;
		virtual void SetInt(const UEString& name, UEInt32 value) override;
		virtual void SetUint(const UEString& name, UEUint32 value) override;
		virtual void SetFloat(const UEString& name, UEFloat value) override;
		virtual void SetDouble(const UEString& name, UEDouble value) override;

		virtual void SetBVec2(const UEString& name, const glm::bvec2& value) override;
		virtual void SetBVec3(const UEString& name, const glm::bvec3& value) override;
		virtual void SetBVec4(const UEString& name, const glm::bvec4& value) override;

		virtual void SetIVec2(const UEString& name, const glm::ivec2& value) override;
		virtual void SetIVec3(const UEString& name, const glm::ivec3& value) override;
		virtual void SetIVec4(const UEString& name, const glm::ivec4& value) override;

		virtual void SetUVec2(const UEString& name, const glm::uvec2& value) override;
		virtual void SetUVec3(const UEString& name, const glm::uvec3& value) override;
		virtual void SetUVec4(const UEString& name, const glm::uvec4& value) override;

		virtual void SetVec2(const UEString& name, const glm::vec2& value) override;
		virtual void SetVec3(const UEString& name, const glm::vec3& value) override;
		virtual void SetVec4(const UEString& name, const glm::vec4& value) override;

		virtual void SetDVec2(const UEString& name, const glm::dvec2& value) override;
		virtual void SetDVec3(const UEString& name, const glm::dvec3& vale) override;
		virtual void SetDVec4(const UEString& name, const glm::dvec4& value) override;

		virtual void SetMat2(const UEString& name, const glm::mat2& value) override;
		virtual void SetMat3(const UEString& name, const glm::mat3& value) override;
		virtual void SetMat4(const UEString& name, const glm::mat4& value) override;

		virtual void SetMat2x2(const UEString& name, const glm::mat2x2& value) override;
		virtual void SetMat2x3(const UEString& name, const glm::mat2x3& value) override;
		virtual void SetMat2x4(const UEString& name, const glm::mat2x4& value) override;

		virtual void SetMat3x2(const UEString& name, const glm::mat3x2& value) override;
		virtual void SetMat3x3(const UEString& name, const glm::mat3x3& value) override;
		virtual void SetMat3x4(const UEString& name, const glm::mat3x4& value) override;

		virtual void SetMat4x2(const UEString& name, const glm::mat4x2& value) override;
		virtual void SetMat4x3(const UEString& name, const glm::mat4x3& value) override;
		virtual void SetMat4x4(const UEString& name, const glm::mat4x4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		UEInt32 GetUniformLocation(const UEString& name);

	private:
		UEUint32 m_ID;
		UEString m_Name;

		UEString m_VertexCode;
		UEString m_FragmentCode;
	};
}