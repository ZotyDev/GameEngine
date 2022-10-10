#include "uepch.h"
#include "Renderer/Shader/ShaderHeaderConstructor.h"

#include <fmt/core.h>

#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	std::array<UEString, (UEUint32)ShaderDataType::Invalid> ShaderHeaderConstructor::s_DataTypeStringIndex =
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

	std::array<UEString, (UEUint32)ShaderHeaderConstructor::UseType::Invalid> ShaderHeaderConstructor::s_UseTypeStringIndex =
	{
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) in {1} {2};\n",
		"layout (location = {0}) out {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
		"layout (location = {0}) uniform {1} {2};\n",
		"layout (binding = {0}) uniform {1} {2};\n",
	};

	std::unordered_map<UEString, ShaderDataType> ShaderHeaderConstructor::s_StringDataTypeIndex = std::unordered_map<UEString, ShaderDataType>() =
	{
		{ "bool", ShaderDataType::Bool },
		{ "int", ShaderDataType::Int },
		{ "uint", ShaderDataType::Uint },
		{ "float", ShaderDataType::Float },
		{ "double", ShaderDataType::Double },

		{ "bvec2", ShaderDataType::BVec2 },
		{ "bvec3", ShaderDataType::BVec3 },
		{ "bvec4", ShaderDataType::BVec4 },

		{ "ivec2", ShaderDataType::IVec2 },
		{ "ivec3", ShaderDataType::IVec3 },
		{ "ivec4", ShaderDataType::IVec4 },

		{ "uvec2", ShaderDataType::UVec2 },
		{ "uvec3", ShaderDataType::UVec3 },
		{ "uvec4", ShaderDataType::UVec4 },

		{ "vec2", ShaderDataType::Vec2 },
		{ "vec3", ShaderDataType::Vec3 },
		{ "vec4", ShaderDataType::Vec4 },

		{ "dvec2", ShaderDataType::DVec2 },
		{ "dvec3", ShaderDataType::DVec3 },
		{ "dvec4", ShaderDataType::DVec4 },

		{ "mat2", ShaderDataType::Mat2 },
		{ "mat3", ShaderDataType::Mat3 },
		{ "mat4", ShaderDataType::Mat4 },

		{ "mat2x2", ShaderDataType::Mat2x2 },
		{ "mat2x3", ShaderDataType::Mat2x3 },
		{ "mat2x4", ShaderDataType::Mat2x4 },

		{ "mat3x2", ShaderDataType::Mat3x2 },
		{ "mat3x3", ShaderDataType::Mat3x3 },
		{ "mat3x4", ShaderDataType::Mat3x4 },

		{ "mat4x2", ShaderDataType::Mat4x2 },
		{ "mat4x3", ShaderDataType::Mat4x3 },
		{ "mat4x4", ShaderDataType::Mat4x4 },

		{ "sampler1D", ShaderDataType::Sampler1D },
		{ "sampler2D", ShaderDataType::Sampler2D },
		{ "sampler3D", ShaderDataType::Sampler3D },
		{ "samplerCube", ShaderDataType::SamplerCube },
		{ "sampler2DRect", ShaderDataType::Sampler2DRect },
		{ "sampler3DRect", ShaderDataType::Sampler3DRect },
		{ "sampler1DArray", ShaderDataType::Sampler1DArray },
		{ "sampler2DArray", ShaderDataType::Sampler2DArray },
		{ "samplerCubeArray", ShaderDataType::SamplerCubeArray },
		{ "samplerBuffer", ShaderDataType::SamplerBuffer },
		{ "sampler2DMS", ShaderDataType::Sampler2DMS },
		{ "sampler2DMSArray", ShaderDataType::Sampler2DMSArray },

		{ "isampler1D", ShaderDataType::ISampler1D },
		{ "isampler2D", ShaderDataType::ISampler2D },
		{ "isampler3D", ShaderDataType::ISampler3D },
		{ "isamplerCube", ShaderDataType::ISamplerCube },
		{ "isampler2DRect", ShaderDataType::ISampler2DRect },
		{ "isampler3DRect", ShaderDataType::ISampler3DRect },
		{ "isampler1DArray", ShaderDataType::ISampler1DArray },
		{ "isampler2DArray", ShaderDataType::ISampler2DArray },
		{ "isamplerCubeArray", ShaderDataType::ISamplerCubeArray },
		{ "isamplerBuffer", ShaderDataType::ISamplerBuffer },
		{ "isampler2DMS", ShaderDataType::ISampler2DMS },
		{ "isampler2DMSArray", ShaderDataType::ISampler2DMSArray },

		{ "usampler1D", ShaderDataType::USampler1D },
		{ "usampler2D", ShaderDataType::USampler2D },
		{ "usampler3D", ShaderDataType::USampler3D },
		{ "usamplerCube", ShaderDataType::USamplerCube },
		{ "usampler2DRect", ShaderDataType::USampler2DRect },
		{ "usampler3DRect", ShaderDataType::USampler3DRect },
		{ "usampler1DArray", ShaderDataType::USampler1DArray },
		{ "usampler2DArray", ShaderDataType::USampler2DArray },
		{ "usamplerCubeArray", ShaderDataType::USamplerCubeArray },
		{ "usamplerBuffer", ShaderDataType::USamplerBuffer },
		{ "usampler2DMS", ShaderDataType::USampler2DMS },
		{ "usampler2DMSArray", ShaderDataType::USampler2DMSArray },

		{ "sampler1DShadow", ShaderDataType::Sampler1DShadow },
		{ "sampler2DShadow", ShaderDataType::Sampler2DShadow },
		{ "samplerCubeShadow", ShaderDataType::SamplerCubeShadow },
		{ "sampler2DRectShadow", ShaderDataType::Sampler2DRectShadow },
		{ "sampler1DArrayShadow", ShaderDataType::Sampler1DArrayShadow },
		{ "sampler2DArrayShadow", ShaderDataType::Sampler2DArrayShadow },
		{ "samplerCubeArrayShadow", ShaderDataType::SamplerCubeArrayShadow }
	};

	UEString ShaderHeaderConstructor::DataTypeToString(ShaderDataType type)
	{
		return s_DataTypeStringIndex[(UEUint32)type];
	}

	UEString ShaderHeaderConstructor::UseTypeToString(ShaderHeaderConstructor::UseType type)
	{
		return s_UseTypeStringIndex[(UEUint32)type];
	}

	ShaderDataType ShaderHeaderConstructor::StringToDataType(const UEString& string)
	{
		if (s_StringDataTypeIndex.find(string) != s_StringDataTypeIndex.end())
		{
			return s_StringDataTypeIndex[string];
		}
		else
		{
			return ShaderDataType::Invalid;
		}
	}

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
			if (it.UseType == ShaderHeaderConstructor::UseType::Invalid)
			{
				UE_CORE_ERROR("Failed to construct shader header: invalid element use type at {}", it.Name);
				return UEResult<>::Error;
			}
			if (it.DataType == ShaderDataType::Invalid)
			{
				UE_CORE_ERROR("Failed to construct shader header: invalid element data type at {}", it.Name);
				return UEResult<>::Error;
			}

			UEString ToBeInserted = UseTypeToString(it.UseType);
			UEString DataTypeString = DataTypeToString(it.DataType);

			switch (it.UseType)
			{
			case ShaderHeaderConstructor::UseType::VertInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertInputCount++, DataTypeToString(it.DataType), "vi_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertOutput:
			{
				ToBeInserted = UseTypeToString(ShaderHeaderConstructor::UseType::VertInput);
				ToBeInserted = fmt::format(ToBeInserted, m_VertInputCount++, DataTypeString, "vi_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();

				ToBeInserted = UseTypeToString(ShaderHeaderConstructor::UseType::VertOutput);
				ToBeInserted = fmt::format(ToBeInserted, m_VertOutputCount++, DataTypeString, "vo_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();

				ToBeInserted = UseTypeToString(ShaderHeaderConstructor::UseType::FragInput);
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, DataTypeString, "fi_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();

				break;
			}
			case ShaderHeaderConstructor::UseType::FragInput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragInputCount++, DataTypeString, "fi_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::FragOutput:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragOutputCount++, DataTypeString, "fo_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::VertUniform:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_VertUniformCount++, DataTypeString, "u_" + it.Name);
				m_VertexSource.insert(m_VertInsertOffset, ToBeInserted);
				m_VertInsertOffset += ToBeInserted.size();
				break;
			}
			case ShaderHeaderConstructor::UseType::FragSampler:
			{
				ToBeInserted = fmt::format(ToBeInserted, m_FragSamplerCount++, DataTypeString, "us_" + it.Name);
				m_FragmentSource.insert(m_FragInsertOffset, ToBeInserted);
				m_FragInsertOffset += ToBeInserted.size();
				break;
			}
			}
		}

		vertSource = m_VertexSource;
		fragSource = m_FragmentSource;

		// MAN THIS IS BIG DEBUG ONLY!!!!!
		UE_CORE_TRACE(m_VertexSource);
		UE_CORE_TRACE(m_FragmentSource);

		return UEResult<>::Success;
	}
}