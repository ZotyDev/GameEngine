#pragma once

#include "Renderer/Camera.h"
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

		Ref<Camera> GetCamera() { return m_Camera; };

	private:
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		float m_ForwardMovement;
		float m_RightMovement;
		float m_UpMovement;
		float m_Velocity;
	private:
		Ref<Camera> m_Camera;
	};
}