#pragma once

#include "UnnamedEngine.h"

namespace UE
{
	class ServerLayer : public Layer
	{
	public:
		ServerLayer(Ref<Application::SharedData> data);
		virtual ~ServerLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnWindowEvent(Event& event) override;
		virtual void OnInputEvent(Event& event) override;

		//void RegisterWindowEvent(std::function<UEBool(Event&)>& fn);
		//void RegisterInputEvent(std::function<UEBool(Event&)>& fn);
	private:
		void Render();
	private:
		Ref<Application::SharedData> m_Data;
	private:
		Ref<Camera> m_Camera;
		Ref<CameraController> m_CameraController;

		Ref<Screen> m_Screen;
		Ref<Primitives::Quad> m_Quad;
	private:
		std::vector<std::function<bool(Event&)>> m_WindowEventFns;
		std::vector<std::function<bool(Event&)>> m_InputEventFns;
	};
}