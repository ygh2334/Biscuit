#pragma once

#include "Biscuit/Renderer/OrthographicCamera.h"
#include "Biscuit/Core/Timestep.h"

#include "Biscuit/Events/ApplicationEvent.h"
#include "Biscuit/Events/MouseEvent.h"

namespace Biscuit
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		OrthographicCamera GetCamera() { return m_Camera; }
		const OrthographicCamera GetCamera() const { return m_Camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3  m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}