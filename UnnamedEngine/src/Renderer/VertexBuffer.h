#pragma once

#include "Renderer/Shader/ShaderDataType.h"

namespace UE
{
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case UE::ShaderDataType::Bool:		return 1;
		case UE::ShaderDataType::Int:		return 4;
		case UE::ShaderDataType::Uint:		return 4;
		case UE::ShaderDataType::Float:		return 4;
		case UE::ShaderDataType::Double:	return 8;
		case UE::ShaderDataType::BVec2:		return 1 * 2;
		case UE::ShaderDataType::BVec3:		return 1 * 3;
		case UE::ShaderDataType::BVec4:		return 1 * 4;
		case UE::ShaderDataType::IVec2:		return 4 * 2;
		case UE::ShaderDataType::IVec3:		return 4 * 3;
		case UE::ShaderDataType::IVec4:		return 4 * 4;
		case UE::ShaderDataType::UVec2:		return 4 * 2;
		case UE::ShaderDataType::UVec3:		return 4 * 3;
		case UE::ShaderDataType::UVec4:		return 4 * 4;
		case UE::ShaderDataType::Vec2:		return 4 * 2;
		case UE::ShaderDataType::Vec3:		return 4 * 3;
		case UE::ShaderDataType::Vec4:		return 4 * 4;
		case UE::ShaderDataType::DVec2:		return 8 * 2;
		case UE::ShaderDataType::DVec3:		return 8 * 3;
		case UE::ShaderDataType::DVec4:		return 8 * 4;
		case UE::ShaderDataType::Mat2:		return 4 * 2 * 2;
		case UE::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case UE::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case UE::ShaderDataType::Mat2x2:	return 4 * 2 * 2;
		case UE::ShaderDataType::Mat2x3:	return 4 * 2 * 3;
		case UE::ShaderDataType::Mat2x4:	return 4 * 2 * 4;
		case UE::ShaderDataType::Mat3x2:	return 4 * 3 * 2;
		case UE::ShaderDataType::Mat3x3:	return 4 * 3 * 3;
		case UE::ShaderDataType::Mat3x4:	return 4 * 3 * 4;
		case UE::ShaderDataType::Mat4x2:	return 4 * 4 * 2;
		case UE::ShaderDataType::Mat4x3:	return 4 * 4 * 3;
		case UE::ShaderDataType::Mat4x4:	return 4 * 4 * 4;
		}

		UE_CORE_ERROR( "Uknown ShaderDataType");
		return 0;
	};

	struct BufferElement
	{
		UEString Name;
		ShaderDataType Type;
		UEUint32 Offset;
		UEUint32 Size;
		UEBool Normalized;

		BufferElement(ShaderDataType type, const UEString& name, UEBool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{};

		UEUint32 GetComponentCount() const
		{
			switch (Type)
			{
			case UE::ShaderDataType::Bool:		return 1;
			case UE::ShaderDataType::Int:		return 1;
			case UE::ShaderDataType::Uint:		return 1;
			case UE::ShaderDataType::Float:		return 1;
			case UE::ShaderDataType::Double:	return 1;
			case UE::ShaderDataType::BVec2:		return 2;
			case UE::ShaderDataType::BVec3:		return 3;
			case UE::ShaderDataType::BVec4:		return 4;
			case UE::ShaderDataType::IVec2:		return 2;
			case UE::ShaderDataType::IVec3:		return 3;
			case UE::ShaderDataType::IVec4:		return 4;
			case UE::ShaderDataType::UVec2:		return 2;
			case UE::ShaderDataType::UVec3:		return 3;
			case UE::ShaderDataType::UVec4:		return 4;
			case UE::ShaderDataType::Vec2:		return 2;
			case UE::ShaderDataType::Vec3:		return 3;
			case UE::ShaderDataType::Vec4:		return 4;
			case UE::ShaderDataType::DVec2:		return 2;
			case UE::ShaderDataType::DVec3:		return 3;
			case UE::ShaderDataType::DVec4:		return 4;
			case UE::ShaderDataType::Mat2:		return 2 * 2;
			case UE::ShaderDataType::Mat3:		return 3 * 3;
			case UE::ShaderDataType::Mat4:		return 4 * 4;
			case UE::ShaderDataType::Mat2x2:	return 2 * 2;
			case UE::ShaderDataType::Mat2x3:	return 2 * 3;
			case UE::ShaderDataType::Mat2x4:	return 2 * 4;
			case UE::ShaderDataType::Mat3x2:	return 3 * 2;
			case UE::ShaderDataType::Mat3x3:	return 3 * 3;
			case UE::ShaderDataType::Mat3x4:	return 3 * 4;
			case UE::ShaderDataType::Mat4x2:	return 4 * 2;
			case UE::ShaderDataType::Mat4x3:	return 4 * 3;
			case UE::ShaderDataType::Mat4x4:	return 4 * 4;
			}

			UE_CORE_ERROR("Uknown ShaderDataType!");

			return 0;
		};
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		};

		UEUint32 GetStride() const { return m_Stride; };
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; };

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			UEUint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		};

	private:
		std::vector<BufferElement> m_Elements;
		UEUint32 m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(UEUint32 size);
		static Ref<VertexBuffer> Create(UEFloat* verticies, UEUint32 size);
	};
}