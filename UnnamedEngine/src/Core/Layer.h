#pragma once

#include "Core/Base.h"

#include "Events/Event.h"
#include "Timestep.h"

namespace UE
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnWindowEvent(Event& event) {}
		virtual void OnInputEvent(Event& event) {}
		//virtual void OnNetworkEvent(Event& event) {}
		virtual void OnRendererEvent(Event& event) {}

		const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}