#include "uepch.h"
#include "Renderer/Shader/ShaderHeaderConstructor.h"

#include <fmt/core.h>

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
	};

	std::array<UEString, (UEUint32)ShaderHeaderConstructor::UseType::Last> ShaderHeaderConstructor::s_UseTypeStringIndex =
	{
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
	};

	ShaderHeaderConstructor::ShaderHeaderConstructor(const UEString& filename)
	{
		std::ifstream VertexFile(filename + ".vert");
		std::ifstream FragmentFile(filename + ".frag");

		std::stringstream VertBuffer;
		std::stringstream FragBuffer;

		VertBuffer << VertexFile.rdbuf();
		m_VertexSource = VertBuffer.str();

		FragBuffer << FragmentFile.rdbuf();
		m_FragmentSource = FragBuffer.str();
	}

	ShaderHeaderConstructor::~ShaderHeaderConstructor()
	{}

	UEResult ShaderHeaderConstructor::AddElement(Element element)
	{
		m_Elements.push_back(element);

		return UEResult::Success;
	}

	UEResult ShaderHeaderConstructor::Construct(UEString& vertSource, UEString& fragSource)
	{
		for (auto& it : m_Elements)
		{
			UEString ToBeInserted = s_UseTypeStringIndex[(UEUint32)it.UseType];
			switch (it.UseType)
			{
			case ShaderHeaderConstructor::UseType::VertInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertOutput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertOutputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();

				ToBeInserted = s_UseTypeStringIndex[(UEUint32)ShaderHeaderConstructor::UseType::FragInput];
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();

				break;
			}
			case ShaderHeaderConstructor::UseType::FragInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::FragOutput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragOutputCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertUniform:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertUniformCount++, s_DataTypeStringIndex[(UEUint32)it.DataType], it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			}
		}

		vertSource = m_VertexSource;
		fragSource = m_FragmentSource;
		UE_CORE_TRACE(m_VertexSource);
		UE_CORE_TRACE(m_FragmentSource);

		return UEResult::Success;
	}
}