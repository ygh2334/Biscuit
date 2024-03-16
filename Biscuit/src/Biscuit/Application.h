#pragma once

#include "Core.h"

#include "Window.h"
#include "Biscuit/LayerStack.h"
#include "Biscuit/Events/Event.h"
#include "Biscuit/Events/ApplicationEvent.h"

namespace Biscuit {

	class BISCUIT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}