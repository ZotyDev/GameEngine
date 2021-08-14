#pragma once

#include "UnnamedEngine.h"

class VoxelGameApp : public UE::Layer
{
public:
	VoxelGameApp();
	virtual ~VoxelGameApp() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(UE::Timestep ts) override;
	virtual void OnEvent(UE::Event& event) override;
private:
	void Render();
private:
	UE::Ref<UE::ShaderLibrary> m_ShaderLibrary = UE::CreateRef<UE::ShaderLibrary>();

	UE::Ref<UE::Texture2D> m_Texture2D;

	UE::Camera m_Camera;
	UE::Ref<UE::CameraController> m_CameraController;

	UE::Ref<UE::Framebuffer> m_Framebuffer;

	UE::Ref<UE::Primitives::Quad> m_Screen;
	UE::Ref<UE::Primitives::Quad> m_Quad;
private:
	bool OnWindowResize(UE::WindowResizeEvent& event);
	bool OnKeyPressed(UE::KeyPressedEvent& event);
	bool OnKeyReleased(UE::KeyReleasedEvent& event);
	bool OnKeyTyped(UE::KeyTypedEvent& event);
	bool OnMousePressed(UE::MouseButtonPressedEvent& event);
	bool OnMouseReleased(UE::MouseButtonReleasedEvent& event);
	bool OnMouseMoved(UE::MouseMovedEvent& event);
	bool OnMouseScrolled(UE::MouseScrolledEvent& event);
	bool OnGamepadButtonPressed(UE::GamepadButtonPressedEvent& event);
	bool OnGamepadButtonReleased(UE::GamepadButtonReleasedEvent& event);
};