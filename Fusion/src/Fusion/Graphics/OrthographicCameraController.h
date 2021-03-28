#pragma once

#include "Fusion/Graphics/OrthographicCamera.h"

#include "Fusion/Core/Timestep.h"
#include "Fusion/Events/Event.h"
#include "Fusion/Events/MouseEvent.h"
#include "Fusion/Events/ApplicationEvent.h"

namespace Fusion { namespace Graphics {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(const float aspectRatio);

		void OnUpdate(const Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

} }
