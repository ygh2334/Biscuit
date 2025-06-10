#pragma once
#include "Biscuit.h"

class Sandbox2D : public Biscuit::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Biscuit::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Biscuit::Event& event) override;
private:

	Biscuit::Ref<Biscuit::Shader> m_FlatColorShader;

	//temp
	Biscuit::Ref<Biscuit::VertexArray> m_SquareVA;
	Biscuit::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0 };
};