#include "bcpch.h"
#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

namespace Biscuit
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation /*= false*/)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		//OnUpdata是每一帧都会调用，而Event是只有激活按键时才会响应，所以镜头移动代码放在这里移动会更加丝滑。
		//这里ts计算了屏幕的刷新时间，会根据屏幕刷新去移动，而不受到OnUpdate的频率影响，保证了不同Update下移动速度相同。
		if (Input::IsKeyPressed(BC_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		else if (Biscuit::Input::IsKeyPressed(BC_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(BC_KEY_W))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(BC_KEY_S))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(BC_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(BC_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BC_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}