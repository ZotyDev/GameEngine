#include "uepch.h"
#include "Script/LuaExposer.h"

#include "Math/Easing/EasingLua.h"

namespace UE
{
	UEResult ExposeCoreToLua(Ref<LunaStack> stack)
	{
		UEResult Result = UEResult::Success;

		Ref<LunaFunction> lEaseInBack = CreateRef<LunaFunction>("EaseInBack", lua_EaseInBack);
		Ref<LunaFunction> lEaseOutBack = CreateRef<LunaFunction>("EaseOutBack", lua_EaseOutBack);
		Ref<LunaFunction> lEaseInOutBack = CreateRef<LunaFunction>("EaseInOutBack", lua_EaseInOutBack);

		Ref<LunaFunction> lEaseInBounce = CreateRef<LunaFunction>("EaseInBounce", lua_EaseInBounce);
		Ref<LunaFunction> lEaseOutBounce = CreateRef<LunaFunction>("EaseOutBounce", lua_EaseOutBounce);
		Ref<LunaFunction> lEaseInOutBounce = CreateRef<LunaFunction>("EaseInOutBounce", lua_EaseInOutBounce);

		Ref<LunaFunction> lEaseInCirc = CreateRef<LunaFunction>("EaseInCirc", lua_EaseInCirc);
		Ref<LunaFunction> lEaseOutCirc = CreateRef<LunaFunction>("EaseOutCirc", lua_EaseOutCirc);
		Ref<LunaFunction> lEaseInOutCirc = CreateRef<LunaFunction>("EaseInOutCirc", lua_EaseInOutCirc);

		Ref<LunaFunction> lEaseInCubic = CreateRef<LunaFunction>("EaseInCubic", lua_EaseInCubic);
		Ref<LunaFunction> lEaseOutCubic = CreateRef<LunaFunction>("EaseOutCubic", lua_EaseOutCubic);
		Ref<LunaFunction> lEaseInOutCubic = CreateRef<LunaFunction>("EaseInOutCubic", lua_EaseInOutCubic);

		Ref<LunaFunction> lEaseInElastic = CreateRef<LunaFunction>("EaseInElastic", lua_EaseInElastic);
		Ref<LunaFunction> lEaseOutElastic = CreateRef<LunaFunction>("EaseOutElastic", lua_EaseOutElastic);
		Ref<LunaFunction> lEaseInOutElastic = CreateRef<LunaFunction>("EaseInOutElastic", lua_EaseInOutElastic);

		Ref<LunaFunction> lEaseInExpo = CreateRef<LunaFunction>("EaseInExpo", lua_EaseInExpo);
		Ref<LunaFunction> lEaseOutExpo = CreateRef<LunaFunction>("EaseOutExpo", lua_EaseOutExpo);
		Ref<LunaFunction> lEaseInOutExpo = CreateRef<LunaFunction>("EaseInOutExpo", lua_EaseInOutExpo);

		Ref<LunaFunction> lEaseInQuad = CreateRef<LunaFunction>("EaseInQuad", lua_EaseInQuad);
		Ref<LunaFunction> lEaseOutQuad = CreateRef<LunaFunction>("EaseOutQuad", lua_EaseOutQuad);
		Ref<LunaFunction> lEaseInOutQuad = CreateRef<LunaFunction>("EaseInOutQuad", lua_EaseInOutQuad);

		Ref<LunaFunction> lEaseInQuart = CreateRef<LunaFunction>("EaseInQuart", lua_EaseInQuart);
		Ref<LunaFunction> lEaseOutQuart = CreateRef<LunaFunction>("EaseOutQuart", lua_EaseOutQuart);
		Ref<LunaFunction> lEaseInOutQuart = CreateRef<LunaFunction>("EaseInOutQuart", lua_EaseInOutQuart);

		Ref<LunaFunction> lEaseInQuint = CreateRef<LunaFunction>("EaseInQuint", lua_EaseInQuint);
		Ref<LunaFunction> lEaseOutQuint = CreateRef<LunaFunction>("EaseOutQuint", lua_EaseOutQuint);
		Ref<LunaFunction> lEaseInOutQuint = CreateRef<LunaFunction>("EaseInOutQuint", lua_EaseInOutQuint);

		Ref<LunaFunction> lEaseInSine = CreateRef<LunaFunction>("EaseInSine", lua_EaseInSine);
		Ref<LunaFunction> lEaseOutSine = CreateRef<LunaFunction>("EaseOutSine", lua_EaseOutSine);
		Ref<LunaFunction> lEaseInOutSine = CreateRef<LunaFunction>("EaseInOutSine", lua_EaseInOutSine);

		LunaModule lEasing("Easing");
		lEasing
			.AddFunction(lEaseInBack)
			.AddFunction(lEaseOutBack)
			.AddFunction(lEaseInOutBack)
			.AddFunction(lEaseInBounce)
			.AddFunction(lEaseOutBounce)
			.AddFunction(lEaseInOutBounce)
			.AddFunction(lEaseInCirc)
			.AddFunction(lEaseOutCirc)
			.AddFunction(lEaseInOutCirc)
			.AddFunction(lEaseInCubic)
			.AddFunction(lEaseOutCubic)
			.AddFunction(lEaseInOutCubic)
			.AddFunction(lEaseInElastic)
			.AddFunction(lEaseOutElastic)
			.AddFunction(lEaseInOutElastic)
			.AddFunction(lEaseInExpo)
			.AddFunction(lEaseOutExpo)
			.AddFunction(lEaseInOutExpo)
			.AddFunction(lEaseInQuad)
			.AddFunction(lEaseOutQuad)
			.AddFunction(lEaseInOutQuad)
			.AddFunction(lEaseInQuart)
			.AddFunction(lEaseInOutQuart)
			.AddFunction(lEaseInQuint)
			.AddFunction(lEaseOutQuint)
			.AddFunction(lEaseInOutQuint)
			.AddFunction(lEaseInSine)
			.AddFunction(lEaseOutSine)
			.AddFunction(lEaseInOutSine);
		
		lEasing.Register(stack);

		return UEResult::Success;
	}
}