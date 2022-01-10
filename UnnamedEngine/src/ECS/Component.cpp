#include "uepch.h"
#include "ECS/Component.h"

namespace UE
{
	UEResult ComponentManager::Add(Ref<ComponentShell> component)
	{
		// todo:zoty check if component is already registered
		m_Components.insert({ component->Name, component });

		return UEResult::Success;
	}

	Ref<ComponentShell> ComponentManager::Get(const UEString& name)
	{
		// todo:zoty check if component exist
		return m_Components.find(name)->second;
	}
}