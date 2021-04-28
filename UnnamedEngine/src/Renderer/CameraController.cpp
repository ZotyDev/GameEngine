#include "uepch.h"
#include "Renderer/CameraController.h"

namespace UE
{
	CameraController::CameraController(Camera3D camera)
		: m_Camera(camera)
	{
	}

	void CameraController::OnUpdate(Timestep timestep)
	{
		m_Camera.Update();
	}

	void CameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	}

	bool CameraController::OnWindowResize(WindowResizeEvent& event)
	{
		m_Camera.SetViewportSize(event.GetWidth(), event.GetHeight());
		return false;
	}
}