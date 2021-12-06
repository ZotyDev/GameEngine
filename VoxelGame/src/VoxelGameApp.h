#pragma once

#include "UnnamedEngine.h"

class VoxelGameApp : public UE::Layer
{
public:
	VoxelGameApp(UE::Ref<UE::Application::SharedData> data);
	virtual ~VoxelGameApp() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(UE::Timestep ts) override;
	virtual void OnWindowEvent(UE::Event& event) override;
	virtual void OnInputEvent(UE::Event& event) override;

	void RegisterWindowEvent(std::function<bool(UE::Event&)>& fn);
	void RegisterInputEvent(std::function<bool(UE::Event&)>& fn);
private:
	void Render();
private:
	UE::Ref<UE::Keyboard> m_Keyboard = UE::CreateRef<UE::Keyboard>();
private:
	UE::Ref<UE::Application::SharedData> m_Data;
private:
	UE::Ref<UE::ShaderLibrary> m_ShaderLibrary = UE::CreateRef<UE::ShaderLibrary>();

	UE::Ref<UE::Texture2D> m_Texture2D;

	UE::Ref<UE::Camera> m_Camera;
	UE::Ref<UE::CameraController> m_CameraController;

	UE::Ref<UE::Screen> m_Screen;
	UE::Ref<UE::Primitives::Quad> m_Quad;
private:
	bool OnWindowResize(UE::WindowResizeEvent& event);
private:
	bool OnKeyPressed(UE::KeyPressedEvent& event);
	bool OnKeyReleased(UE::KeyReleasedEvent& event);
	bool OnKeyTyped(UE::KeyTypedEvent& event);
	bool OnMousePressed(UE::MouseButtonPressedEvent& event);
	bool OnMouseReleased(UE::MouseButtonReleasedEvent& event);
	bool OnMouseMoved(UE::MouseMovedEvent& event);
	bool OnMouseScrolled(UE::MouseScrolledEvent& event);
	bool OnGamepadButtonPressed(UE::GamepadButtonPressedEvent& event);
	bool OnGamepadButtonReleased(UE::GamepadButtonReleasedEvent& event);
private:
	std::vector<std::function<bool(UE::Event&)>> m_WindowEventFns;
	std::vector<std::function<bool(UE::Event&)>> m_InputEventFns;
};