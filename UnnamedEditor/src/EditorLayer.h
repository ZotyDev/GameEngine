#pragma once

#include <UnnamedEngine.h>

#include "Panels/MenuBarPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"
#include "Panels/ProfilerPanel.h"
#include "Panels/NodeEditorPanel/NodeEditorPanel.h"

namespace UE
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(Ref<Application::SharedData> data);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnWindowEvent(Event& event) override;
		virtual void OnInputEvent(Event& event) override;

		void RegisterWindowEvent(std::function<bool(Event&)>& fn);
		void RegisterInputEvent(std::function<bool(Event&)>& fn);
	private:
		void Render();
	private:
		Ref<Application::SharedData> m_Data;
	private:
		Ref<Keyboard> m_Keyboard = CreateRef<UE::Keyboard>();
	private:
		Ref<Camera> m_Camera;
		Ref<CameraController> m_CameraController;

		Ref<Texture2D> m_Texture2D;
		
		Ref<Screen> m_Screen;
		Ref<Primitives::Quad> m_Quad;
	private:
		MenuBarPanel m_MenuBarPanel;
		ViewportPanel m_ViewportPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		PropertiesPanel m_PropertiesPanel;
		ProfilerPanel m_ProfilerPanel;
		NodeEditorPanel m_NodeEditorPanel;
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