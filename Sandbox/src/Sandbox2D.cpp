#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Biscuit/Renderer/Shader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sanbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Biscuit::VertexArray::Create();
	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Biscuit::Ref<Biscuit::VertexBuffer> squareVB;
	squareVB.reset(Biscuit::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	squareVB->SetLayout(
		{
			{Biscuit::ShaderDataType::Float3, "a_Position"}
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
	Biscuit::Ref<Biscuit::IndexBuffer> squareIB;
	squareIB.reset(Biscuit::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Biscuit::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Biscuit::Timestep ts)
{
	//update
	m_CameraController.OnUpdate(ts);

	//render
	Biscuit::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Biscuit::RenderCommand::Clear();

	Biscuit::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Biscuit::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
	Biscuit::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Biscuit::Event& event)
{
	m_CameraController.OnEvent(event);
}
