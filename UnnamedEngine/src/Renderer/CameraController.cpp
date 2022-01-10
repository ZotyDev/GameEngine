#include "uepch.h"
#include "Renderer/CameraController.h"

namespace UE
{
	CameraController::CameraController(Ref<Camera> camera)
		: m_Camera(camera), m_ForwardMovement(0.0f), m_RightMovement(0.0f), m_UpMovement(0.0f), m_Velocity(5.0f)
	{}

	void CameraController::OnUpdate(Timestep timestep)
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + (m_Camera->GetForwardDirection() * m_ForwardMovement * m_Velocity * timestep.GetSeconds()));
		m_Camera->SetPosition(m_Camera->GetPosition() + (m_Camera->GetRightDirection() * m_RightMovement * m_Velocity * timestep.GetSeconds()));
		m_Camera->SetPosition(m_Camera->GetPosition() + (m_Camera->GetUpDirection() * m_UpMovement * m_Velocity * timestep.GetSeconds()));

		m_Camera->Update();
	}

	void CameraController::MoveForward()
	{
		m_ForwardMovement = 1.0f;
	}

	void CameraController::MoveBackward()
	{
		m_ForwardMovement = -1.0f;
	}

	void CameraController::StopForward()
	{
		m_ForwardMovement = 0.0f;
	}

	void CameraController::MoveRight()
	{
		m_RightMovement = 1.0f;
	}

	void CameraController::MoveLeft()
	{
		m_RightMovement = -1.0f;
	}

	void CameraController::StopRight()
	{
		m_RightMovement = 0.0f;
	}

	void CameraController::MoveUp()
	{
		m_UpMovement = 1.0f;
	}

	void CameraController::MoveDown()
	{
		m_UpMovement = -1.0f;
	}

	void CameraController::StopUp()
	{
		m_UpMovement = 0.0f;
	}

	void CameraController::OnResize(float width, float height)
	{
		m_Camera->SetViewportSize(width, height);
	}

	void CameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	}

	bool CameraController::OnWindowResize(WindowResizeEvent& event)
	{
		m_Camera->SetViewportSize((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}

}