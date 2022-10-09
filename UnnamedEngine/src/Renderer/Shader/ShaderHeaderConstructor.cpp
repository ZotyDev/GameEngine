#include "uepch.h"
#include "Renderer/Shader/ShaderHeaderConstructor.h"

#include <fmt/core.h>

#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	std::array<UEString, (UEUint32)ShaderDataType::Last> ShaderHeaderConstructor::s_DataTypeStringIndex =
	{
		"bool",		"int",		"uint",		"float",	"double",
		"bvec2",	"bvec3",	"bvec4",
		"ivec2",	"ivec3",	"ivec4",
		"uvec2",	"uvec3",	"uvec4",
		"vec2",		"vec3",		"vec4,",
		"dvec2",	"dvec3",	"dvec4",
		"mat2",		"mat3",		"mat4",
		"mat2x2",	"mat2x3",	"mat2x4",
		"mat3x2",	"mat3x3",	"mat3x4",
		"mat4x2",	"mat4x3",	"mat4x4",

		"sampler1D", "sampler2D", "sampler3D", "samplerCube", "sampler2DRect", "sampler3DRect", "sampler1DArray", "sampler2DArray", "samplerCubeArray", "samplerBuffer", "sampler2DMS", "sampler2DMSArray",
		"isampler1D", "isampler2D", "isampler3D", "isamplerCube", "isampler2DRect", "isampler3DRect", "isampler1DArray", "isampler2DArray", "isamplerCubeArray", "isamplerBuffer", "isampler2DMS", "isampler2DMSArray",
		"usampler1D", "usampler2D", "usampler3D", "usamplerCube", "usampler2DRect", "usampler3DRect", "usampler1DArray", "usampler2DArray", "usamplerCubeArray", "usamplerBuffer", "usampler2DMS", "usampler2DMSArray",
		"sampler1DShadow", "sampler2DShadow", "samplerCubeShadow", "sampler2DRectShadow", "sampler1DArrayShadow", "sampler2DArrayShadow", "samplerCubeArrayShadow",

	};

	std::array<UEString, (UEUint32)ShaderHeaderConstructor::UseType::Last> ShaderHeaderConstructor::s_UseTypeStringIndex =
	{
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
		"layout (binding = {0}) uniform {1} {2};\n",
	};

	ShaderHeaderConstructor::ShaderHeaderConstructor(const UEPath& path)
	{
		UEPath VertexPath = path;
		VertexPath += ".vert";
		
		UEPath FragmentPath = path;
		FragmentPath += ".frag";

		FileSystem::ReadToBuffer(VertexPath, m_VertexSource);
		FileSystem::ReadToBuffer(FragmentPath, m_FragmentSource);
	}

	ShaderHeaderConstructor::~ShaderHeaderConstructor()
	{}

	UEResult<> ShaderHeaderConstructor::SetElements(const std::vector<Element>& elements)
	{
		m_Elements = elements;

		return UEResult<>::Success;
	}

	UEResult<> ShaderHeaderConstructor::Construct(UEString& vertSource, UEString& fragSource)
	{
		for (auto& it : m_Elements)
		{
			UEString ToBeInserted = s_UseTypeStringIndex[(UEUint32)it.UseType];
			switch (it.UseType)
			{
			case ShaderHeaderConstructor::UseType::VertInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "vi_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertOutput:
			{
				ToBeInserted = s_UseTypeStringIndex[(UEUint32)ShaderHeaderConstructor::UseType::VertInput];
				ToBeInserted = fmt::format(ToBeInserted, m_VertInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "vi_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();

				ToBeInserted = s_UseTypeStringIndex[(UEUint32)ShaderHeaderConstructor::UseType::VertOutput];
				ToBeInserted = fmt::format(ToBeInserted, m_VertOutputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "vo_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();

				ToBeInserted = s_UseTypeStringIndex[(UEUint32)ShaderHeaderConstructor::UseType::FragInput];
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "fi_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();

				break;
			}
			case ShaderHeaderConstructor::UseType::FragInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "fi_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::FragOutput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragOutputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "fo_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertUniform:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertUniformCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "u_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::FragSampler:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragSamplerCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], "us_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			}
		}

		vertSource = m_VertexSource;
		fragSource = m_FragmentSource;
		UE_CORE_TRACE(m_VertexSource);
		UE_CORE_TRACE(m_FragmentSource);

		return UEResult<>::Success;
	}
}