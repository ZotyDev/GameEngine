#pragma once

#include "Script/Luna/LunaStack.h"
#include "Script/Luna/LunaFunction.h"
#include "Script/Luna/LunaModule.h"

namespace UE
{
	UEResult ExposeCoreToLua(Ref<LunaStack> stack);
}