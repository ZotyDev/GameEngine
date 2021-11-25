#pragma once

#include "ECS/Entity.h"

#define UE_COMPONENT_INCREMENT_SLICE 128

namespace UE
{
	struct ComponentDataShell
	{
		ComponentDataShell() {}
		ComponentDataShell(const UEString& name, UEType type, UEUint32 size)
			: Name(name), Type(type), Size(size)
		{
			switch (type)
			{
			case UE::UEType::Bool:
				Data = new UEBool[size];
				break;
			case UE::UEType::Char:
				Data = new UEChar[size];
				break;
			case UE::UEType::Int8:
				Data = new UEInt8[size];
				break;
			case UE::UEType::Int16:
				Data = new UEInt16[size];
				break;
			case UE::UEType::Int32:
				Data = new UEInt32[size];
				break;
			case UE::UEType::Int64:
				Data = new UEInt64[size];
				break;
			case UE::UEType::Uint8:
				Data = new UEUint8[size];
				break;
			case UE::UEType::Uint16:
				Data = new UEUint16[size];
				break;
			case UE::UEType::Uint32:
				Data = new UEUint32[size];
				break;
			case UE::UEType::Uint64:
				Data = new UEUint64[size];
				break;
			case UE::UEType::Float:
				Data = new UEFloat[size];
				break;
			case UE::UEType::Double:
				Data = new UEDouble[size];
				break;
			default:
				break;
			}
		}

		//template<typename T>
		//T GetData()
		//{
		//	return *(T*)Data;
		//}

		void Delete()
		{
			delete[] Data;
		}

		UEString Name;
		UEUint32 Size;
		UEType Type;
		void* Data;
	};

	struct ComponentShell
	{
		~ComponentShell()
		{
			for (auto it : DataList)
			{
				it.Delete();
			}
		}

		UEString Name;
		std::vector<ComponentDataShell> DataList;
	};

	class ComponentLibrary
	{
	public:

		UEResult RegisterComponent(Ref<ComponentShell> component);

	private:
		std::unordered_map<UEString, Ref<ComponentShell>> m_Components;
	};

	/* 
	* Position
	* Direction
	* Velocity
	* Sound
	* Name
	* Health
	* Mana
	* Inventory
	* XP
	* Brightness
	* Hunger
	* Thirst
	*/

	struct Component
	{
		float X[UE_MAX_ENTITIES];
		float Y[UE_MAX_ENTITIES];
		float Z[UE_MAX_ENTITIES];
	};
}