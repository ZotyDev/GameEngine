#pragma once

#include "Core/Layer.h"

#include "Events/windowEvent.h"
#include "Events/keyEvent.h"
#include "Events/mouseEvent.h"

namespace UE
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnWindowEvent(Event& event) = 0;
		virtual void OnInputEvent(Event& event) = 0;

		virtual void Begin() = 0;
		virtual void End() = 0;

		void BlockEvents(bool block) { m_BlockingEvents = block; }
		
		void SetDarkThemeColors();

		static Ref<ImGuiLayer> Create();
	protected:
		bool m_BlockingEvents = true;
	};
}