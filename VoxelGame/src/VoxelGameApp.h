#pragma once

#include "UnnamedEngine.h"

class VoxelGameApp : public UE::Layer
{
public:
	VoxelGameApp();
	virtual ~VoxelGameApp() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(UE::Timestep ts) override;
	void OnEvent(UE::Event& event) override;
private:
	UE::Ref<UE::ShaderLibrary> m_ShaderLibrary = UE::CreateRef<UE::ShaderLibrary>();

	UE::Ref<UE::Texture2D> m_Texture2D;

	UE::Camera3D m_Camera;
	UE::Ref<UE::CameraController> m_CameraController;

	UE::Ref<UE::Framebuffer> m_Framebuffer;

	UE::Ref<UE::Primitives::Quad> m_Screen;
	UE::Ref<UE::Primitives::Quad> m_Quad;
private:
	bool OnWindowResize(UE::WindowResizeEvent& event);
};