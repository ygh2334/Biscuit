#include <Biscuit.h>
#include "Biscuit/Log.cpp"

class ExampleLayer : public Biscuit::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Biscuit::Input::IsKeyPressed(BC_KEY_TAB))
			BC_INFO("Tab key is pressed!");

	}

	void OnEvent(Biscuit::Event& event) override
	{
		BC_TRACE("{0}", event);
		if (event.GetEventType() == Biscuit::EventType::KeyPressed)
		{
			Biscuit::KeyPressedEvent& e = (Biscuit::KeyPressedEvent&)event;
			BC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox :public Biscuit::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverLay(new Biscuit::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Biscuit::Application* Biscuit::CreateApplication()
{
	return new Sandbox();
}