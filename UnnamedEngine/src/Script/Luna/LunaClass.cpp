#include "uepch.h"
#include "Script/Luna/LunaClass.h"

namespace UE
{
	LunaClass::LunaClass(UEString name)
		: m_Name(name)
	{}

	LunaClass::~LunaClass()
	{}

	UEResult LunaClass::AddMethod(const UEString& name, lua_CFunction method)
	{


		return UEResult::Success;
	}


}