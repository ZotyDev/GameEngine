#include "uepch.h"
#include "Script/LuaExposer.h"

#include "Math/Easing/EasingLua.h"
#include "Core/LogLua.h"

namespace UE
{
	UEResult ExposeCoreToLua(LuneStack stack)
	{
		LuneModule Core("Core");
		Core
			.Add(LuneModule("Math")
				.Add(LuneModule("Easing")
					.Add("EaseInBack", lua_EaseInBack)
					.Add("EaseOutBack", lua_EaseOutBack)
					.Add("EaseInOutBack", lua_EaseInOutBack)
					.Add("EaseInBounce", lua_EaseInBounce)
					.Add("EaseOutBounce", lua_EaseOutBounce)
					.Add("EaseInOutBounce", lua_EaseInOutBounce)
					.Add("EaseInCirc", lua_EaseInCirc)
					.Add("EaseOutCirc", lua_EaseOutCirc)
					.Add("EaseInOutCirc", lua_EaseInOutCirc)
					.Add("EaseInCubic", lua_EaseInCubic)
					.Add("EaseOutCubic", lua_EaseOutCubic)
					.Add("EaseInOutCubic", lua_EaseInOutCubic)
					.Add("EaseInElastic", lua_EaseInElastic)
					.Add("EaseOutElastic", lua_EaseOutElastic)
					.Add("EaseInOutElastic", lua_EaseInOutElastic)
					.Add("EaseInExpo", lua_EaseInExpo)
					.Add("EaseOutExpo", lua_EaseOutExpo)
					.Add("EaseInOutExpo", lua_EaseInOutExpo)
					.Add("EaseInQuad", lua_EaseInQuad)
					.Add("EaseOutQuad", lua_EaseOutQuad)
					.Add("EaseInOutQuad", lua_EaseInOutQuad)
					.Add("EaseInQuart", lua_EaseInQuart)
					.Add("EaseOutQuart", lua_EaseOutQuart)
					.Add("EaseInOutQuart", lua_EaseInOutQuart)
					.Add("EaseInQuint", lua_EaseInQuint)
					.Add("EaseOutQuint", lua_EaseOutQuint)
					.Add("EaseInOutQuint", lua_EaseInOutQuint)
					.Add("EaseInSine", lua_EaseInSine)
					.Add("EaseOutSine", lua_EaseOutSine)
					.Add("EaseInOutSine", lua_EaseInOutSine)
				) // Easing
			) // Math
			.Add(LuneClass("Logger")
				.AddCtor("Create", lua_CreateLogger)
				.AddCtor("Get", lua_GetLogger)
				.Add("Trace", lua_LoggerTrace)
				.Add("Info", lua_LoggerInfo)
				.Add("Warn", lua_LoggerWarn)
				.Add("Error", lua_LoggerError)
				.Add("Critical", lua_LoggerCritical)
			); // Logger
		
		Core.Register(stack);

		return UEResult::Success;
	}
}