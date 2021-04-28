#pragma once

#include "Renderer/Camera3D.h"
#include "Core/Timestep.h"

#include "Events/WindowEvent.h"

namespace UE
{
	class CameraController
	{
	public:
		CameraController(Camera3D camera);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		Camera3D& GetCamera() { return m_Camera; };
		const Camera3D& GetCamera() const { return m_Camera; }

	private:
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		Camera3D m_Camera;
	};
}