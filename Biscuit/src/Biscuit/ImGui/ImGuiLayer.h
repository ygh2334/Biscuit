#pragma once

#include "Biscuit/Layer.h"
#include "Biscuit/Events/KeyEvent.h"
#include "Biscuit/Events/MouseEvent.h"
#include "Biscuit/Events/ApplicationEvent.h"

namespace Biscuit
{
	class BISCUIT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowsResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;

	};
}