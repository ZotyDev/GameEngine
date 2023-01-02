#pragma once

#include "UnnamedEngine.h"

namespace UE
{
	class UnnamedClientApp : public Layer
	{
	public:
		UnnamedClientApp(Ref<Application::SharedData> data);
		virtual ~UnnamedClientApp() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnWindowEvent(Event& event) override;
		virtual void OnInputEvent(Event& event) override;
		//virtual void OnNetworkEvent(Event& event) override;
		virtual void OnRendererEvent(Event& event) override;

		void RegisterWindowEvent(std::function<bool(Event&)>& fn);
		void RegisterInputEvent(std::function<bool(Event&)>& fn);
	private:
		void Render();
	private:
		Ref<Keyboard> m_Keyboard = CreateRef<UE::Keyboard>();
	private:
		Ref<Application::SharedData> m_Data;
	private:
		Ref<Texture2D> m_Texture2D;

		Ref<Camera> m_Camera;
		Ref<CameraController> m_CameraController;

		Ref<Screen> m_Screen;
		Ref<Primitives::Quad> m_Quad;
	private:
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnMousePressed(MouseButtonPressedEvent& event);
		bool OnMouseReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnGamepadButtonPressed(GamepadButtonPressedEvent& event);
		bool OnGamepadButtonReleased(GamepadButtonReleasedEvent& event);
	private:
		bool OnRendererScaleChange(RendererScaleChangeEvent& event);
	private:
		std::vector<std::function<bool(Event&)>> m_WindowEventFns;
		std::vector<std::function<bool(Event&)>> m_InputEventFns;
	};
}