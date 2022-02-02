#pragma once

#include "Renderer/Shader/ShaderDataType.h"

namespace UE
{
	class ShaderHeaderConstructor
	{
	public:
		enum class UseType
		{
			VertInput	= 0,
			VertOutput	= 1,

			FragInput   = 2,
			FragOutput  = 3,

			VertUniform = 4,
			FragUniform = 5,

			FragSampler = 6,

			Last
		};

		struct Element
		{
			UEString Name;
			ShaderDataType DataType;
			ShaderHeaderConstructor::UseType UseType;
		};

	public:
		ShaderHeaderConstructor(const UEPath& path);
		~ShaderHeaderConstructor();

		UEResult SetElements(const std::vector<Element>& elements);

		UEResult Construct(UEString& vertSource, UEString& fragSource);
	
	private:
		static std::array<UEString, (UEUint32)ShaderDataType::Last> s_DataTypeStringIndex;
		static std::array<UEString, (UEUint32)ShaderHeaderConstructor::UseType::Last> s_UseTypeStringIndex;
	private:
		UEString m_VertexSource;
		UEString m_FragmentSource;
	private:
		std::vector<Element> m_Elements;
		UEUint32 m_VertInsertOffset = 19;
		UEUint32 m_FragInsertOffset = 19;

		UEUint8 m_VertInputCount = 0;
		UEUint8 m_VertOutputCount = 0;
		UEUint8 m_VertUniformCount = 0;
		
		UEUint8 m_FragInputCount = 0;
		UEUint8 m_FragOutputCount = 0;
		UEUint8 m_FragUniformCount = 0;
		UEUint8 m_FragSamplerCount = 0;
	};
}