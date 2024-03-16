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
		BC_INFO("ExampleLayer::Update");
	}

	void OnEvent(Biscuit::Event& event) override
	{
		BC_TRACE("{0}", event);
	}
};

class Sandbox :public Biscuit::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Biscuit::Application* Biscuit::CreateApplication()
{
	return new Sandbox();
}