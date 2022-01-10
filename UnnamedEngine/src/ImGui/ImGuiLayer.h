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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnWindowEvent(Event& event) override;
		virtual void OnInputEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockingEvents = block; }
		
		void SetDarkThemeColors();
	private:
		bool m_BlockingEvents = true;
	};
}