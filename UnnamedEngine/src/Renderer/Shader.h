#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace UE
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual UEResult<> LoadFromSource(const UEPath& path) = 0;
		virtual UEResult<> LoadFromSource(const UEString& name, const UEPath& vertexPath, const UEPath& fragmentPath) = 0;

		virtual UEResult<> Compile() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Set(const UEString& vertSource, const UEString& fragSource) = 0;

		virtual void SetBool(const UEString& name, UEBool value) = 0;
		virtual void SetInt(const UEString& name, UEInt32 value) = 0;
		virtual void SetUint(const UEString& name, UEUint32 value) = 0;
		virtual void SetFloat(const UEString& name, UEFloat value) = 0;
		virtual void SetDouble(const UEString& name, UEDouble value) = 0;

		virtual void SetBVec2(const UEString& name, const glm::bvec2& value) = 0;
		virtual void SetBVec3(const UEString& name, const glm::bvec3& value) = 0;
		virtual void SetBVec4(const UEString& name, const glm::bvec4& value) = 0;

		virtual void SetIVec2(const UEString& name, const glm::ivec2& value) = 0;
		virtual void SetIVec3(const UEString& name, const glm::ivec3& value) = 0;
		virtual void SetIVec4(const UEString& name, const glm::ivec4& value) = 0;

		virtual void SetUVec2(const UEString& name, const glm::uvec2& value) = 0;
		virtual void SetUVec3(const UEString& name, const glm::uvec3& value) = 0;
		virtual void SetUVec4(const UEString& name, const glm::uvec4& value) = 0;

		virtual void SetVec2(const UEString& name, const glm::vec2& value) = 0;
		virtual void SetVec3(const UEString& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const UEString& name, const glm::vec4& value) = 0;

		virtual void SetDVec2(const UEString& name, const glm::dvec2& value) = 0;
		virtual void SetDVec3(const UEString& name, const glm::dvec3& vale) = 0;
		virtual void SetDVec4(const UEString& name, const glm::dvec4& value) = 0;
		
		virtual void SetMat2(const UEString& name, const glm::mat2& value) = 0;
		virtual void SetMat3(const UEString& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const UEString& name, const glm::mat4& value) = 0;

		virtual void SetMat2x2(const UEString& name, const glm::mat2x2& value) = 0;
		virtual void SetMat2x3(const UEString& name, const glm::mat2x3& value) = 0;
		virtual void SetMat2x4(const UEString& name, const glm::mat2x4& value) = 0;

		virtual void SetMat3x2(const UEString& name, const glm::mat3x2& value) = 0;
		virtual void SetMat3x3(const UEString& name, const glm::mat3x3& value) = 0;
		virtual void SetMat3x4(const UEString& name, const glm::mat3x4& value) = 0;

		virtual void SetMat4x2(const UEString& name, const glm::mat4x2& value) = 0;
		virtual void SetMat4x3(const UEString& name, const glm::mat4x3& value) = 0;
		virtual void SetMat4x4(const UEString& name, const glm::mat4x4& value) = 0;

		virtual const UEString& GetName() const = 0;

		static Ref<Shader> Create();
	};

	class ShaderLibrary
	{
	public:
		static void Add(const UEString& name, const Ref<Shader>& shader);
		static void Add(const Ref<Shader>& shader);
		static UEResult<> Load(const UEPath& path);
		static UEResult<> Load(const UEString& name, const UEPath& path);

		static Ref<Shader> Get(const UEString& name);

		static bool Exists(const UEString& name);
	private:
		static std::unordered_map<UEString, Ref<Shader>> m_Shaders;
	};
}