#pragma once

#include "Renderer/Camera2D.h"
#include "Renderer/Camera3D.h"
#include "Core/Timestep.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"

namespace UE
{
	class CameraController
	{
	public:
		CameraController(Ref<Camera> camera);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		void MoveForward();
		void MoveBackward();
		void StopForward();

		void MoveRight();
		void MoveLeft();
		void StopRight();

		void MoveUp();
		void MoveDown();
		void StopUp();

		void OnResize(UEFloat width, UEFloat height);

		Ref<Camera> GetCamera() { return m_Camera; };

	private:
		UEBool OnWindowResize(WindowResizeEvent& event);
	private:
		UEFloat m_ForwardMovement;
		UEFloat m_RightMovement;
		UEFloat m_UpMovement;
		UEFloat m_Velocity;
	private:
		Ref<Camera> m_Camera;
	};
}