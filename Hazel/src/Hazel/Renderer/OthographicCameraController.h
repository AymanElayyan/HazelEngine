#pragma once

#include "Hazel/Renderer/OthographicCamera.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	class OthographicCameraControll
	{
	public:
		OthographicCameraControll(float aspecRatio, bool rotation = false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspecRatio;
		float m_ZoomLevel = 1.0f;
		OthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		float m_RotationPosition = 0.0f;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 1.0f;



	};
}
