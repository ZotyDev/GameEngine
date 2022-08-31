#include "uepch.h"
#include "FreeType/FreeTypeTextAPI.h"

namespace UE
{
	FreeTypeTextAPI::~FreeTypeTextAPI()
	{
		FT_Done_FreeType(FreeType);
	}

	UEResult<> FreeTypeTextAPI::Init()
	{
		if (FT_Init_FreeType(&FreeType))
		{
			UE_CORE_ERROR("Could not initialize FreeType");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	void* FreeTypeTextAPI::GetRawLibrary()
	{
		return (void*)FreeType;
	}
}