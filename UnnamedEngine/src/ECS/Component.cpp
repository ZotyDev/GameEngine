#include "uepch.h"
#include "ECS/Component.h"

namespace UE
{
	UEResult ComponentLibrary::RegisterComponent(Ref<ComponentShell> component)
	{
		// todo:zoty check if component is already registered
		m_Components.insert({ component->Name, component });

		return UEResult::Success;
	}
}