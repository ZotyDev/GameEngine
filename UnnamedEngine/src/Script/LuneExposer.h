#pragma once

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	UEResult<> ExposeCoreToLune(Ref<LuneStack> stack);
}