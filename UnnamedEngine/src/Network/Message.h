#pragma once

#include "Network/NetworkAPI.h"

#define MAX_MESSAGE_SIZE 1024
#define MESSAGE_ARRAY_MAX_SIZE MAX_MESSAGE_SIZE / 64

#include "Core/Bitpacker.h"

namespace UE
{
	struct MessageLayout
	{
		MessageLayout(const std::vector<UEVDescriptor>& elements);
		std::vector<UEVDescriptor> Elements;
	};

	struct MessageLayoutData
	{
		MessageLayoutData() = default;
		MessageLayoutData(const std::vector<UEVValue>& elements);
		std::vector<UEVValue> Elements;
	};

	class MessageLayoutLibrary
	{
	public:
		UEResult RegisterMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout);
		UEResult LoadMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout);

	private:
		std::unordered_map<std::string, Ref<MessageLayout>> m_MessageLayouts;
	};

	class Message
	{
	public:
		Message(Ref<MessageLayout> layout);

		UEResult PackData(Ref<MessageLayoutData> layoutData)
		{
			// check for size
			UEUint32 LayoutDataSize = layoutData->Elements.size();
			UEUint32 LayoutSize = m_Layout->Elements.size();
			if (LayoutDataSize != LayoutSize)
			{
				UE_CORE_ERROR("Failed to pack message data: expected {0} elements, received {1}", LayoutSize, LayoutDataSize);
				return UEResult::Error;
			}

			// pack everything to buffer
			for (UEUint32 i = 0; i < LayoutSize; i++)
			{
				UEVDescriptor Element = m_Layout->Elements[i];
				UEVValue ElementData = layoutData->Elements[i];

				switch (Element.Type)
				{
				case UEType::Bool: 
					m_Bitpacker.PackBits(ElementData.Bool, Element.Range); 
					break;
				case UEType::Char:
					m_Bitpacker.PackBits(ElementData.Char, Element.Range); 
					break;
				case UEType::Int8:
					if (ElementData.Int8 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Int8);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Int8, Element.Range);
					break;
				case UEType::Int16:
					if (ElementData.Int16 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Int16);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Int16, Element.Range);
					break;
				case UEType::Int32:
					if (ElementData.Int32 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Int32);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Int32, Element.Range);
					break;
				case UEType::Int64:
					if (ElementData.Int64 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Int64);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Int64, Element.Range);
					break;
				case UEType::Uint8:
					if (ElementData.Uint8 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Uint8);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Uint8, Element.Range);
					break;
				case UEType::Uint16:
					if (ElementData.Uint16 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Uint16);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Uint16, Element.Range);
					break;
				case UEType::Uint32:
					if (ElementData.Uint32 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Uint32);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Uint32, Element.Range);
					break;
				case UEType::Uint64:
					if (ElementData.Uint64 > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Uint64);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Uint64, Element.Range);
					break;
				case UEType::Float:
					if (ElementData.Float > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Float);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Float, Element.Range);
					break;
				case UEType::Double:
					if (ElementData.Double > Element.Range)
					{
						UE_CORE_ERROR("Failed to pack data: element {0} out of range. Max is {1}, received {2}", Element.Name, Element.Range, ElementData.Double);
						return UEResult::Error;
					}
					m_Bitpacker.PackBits(ElementData.Double, Element.Range);
					break;
				default:
					break;
				}
			}
			m_Bitpacker.EndPacking();

			// convert uint64 buffer into char buffer
			for (UEUint32 i = 0; i < m_Bitpacker.m_RawData.size(); i++)
			{

			}

			return UEResult::Success;
		}

		UEResult UnpackData(Ref<MessageLayoutData> data)
		{
			// convert char buffer into uint64 buffer

			UEUint32 LayoutSize = m_Layout->Elements.size();

			data->Elements.resize(LayoutSize);

			// unpack everything to buffer
			for (UEUint32 i = 0; i < LayoutSize; i++)
			{
				UEVDescriptor Element = m_Layout->Elements[i];

				switch (Element.Type)
				{
				case UEType::Bool:
					m_Bitpacker.UnpackBits(data->Elements[i].Bool, Element.Range);
					break;
				case UEType::Char:
					m_Bitpacker.UnpackBits(data->Elements[i].Char, Element.Range);
					break;
				case UEType::Int8:
					m_Bitpacker.UnpackBits(data->Elements[i].Int8, Element.Range);
					break;
				case UEType::Int16:
					m_Bitpacker.UnpackBits(data->Elements[i].Int16, Element.Range);
					break;
				case UEType::Int32:
					m_Bitpacker.UnpackBits(data->Elements[i].Int32, Element.Range);
					break;
				case UEType::Int64:
					m_Bitpacker.UnpackBits(data->Elements[i].Int64, Element.Range);
					break;
				case UEType::Uint8:
					m_Bitpacker.UnpackBits(data->Elements[i].Uint8, Element.Range);
					break;
				case UEType::Uint16:
					m_Bitpacker.UnpackBits(data->Elements[i].Uint16, Element.Range);
					break;
				case UEType::Uint32:
					m_Bitpacker.UnpackBits(data->Elements[i].Uint32, Element.Range);
					break;
				case UEType::Uint64:
					m_Bitpacker.UnpackBits(data->Elements[i].Uint64, Element.Range);
					break;
				case UEType::Float:
					m_Bitpacker.UnpackBits(data->Elements[i].Float, Element.Range);
					break;
				case UEType::Double:
					m_Bitpacker.UnpackBits(data->Elements[i].Double, Element.Range);
					break;
				default:
					break;
				}
			}
			return UEResult::Success;
		}

	private:
		Ref<MessageLayout> m_Layout;
	private:
		UEUint64 m_Packer = 0;
		UEUint32 m_CurrentPacked = 0;
		UEUint8 m_PackerIndex = 0;

		Bitpacker m_Bitpacker;
	private:
		std::vector<UEChar> m_Buffer;
	};
}