#include <Biscuit.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Biscuit::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, 1.6, -0.9, 0.9), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Biscuit::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.2f,0.8f,1.0f,
			0.5f,-0.5f,0.0f,0.2f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.8f,0.8f,0.2f,1.0f
		};

		Biscuit::Ref<Biscuit::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Biscuit::VertexBuffer::Create(vertices, sizeof(vertices)));
		Biscuit::BufferLayout layout = {
			{Biscuit::ShaderDataType::Float3, "a_Position"},
			{Biscuit::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Biscuit::Ref<Biscuit::IndexBuffer> indexBuffer;
		indexBuffer.reset(Biscuit::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Biscuit::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Biscuit::Ref<Biscuit::VertexBuffer> squareVB;
		squareVB.reset(Biscuit::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout(
			{
				{Biscuit::ShaderDataType::Float3, "a_Position"},
				{Biscuit::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Biscuit::Ref<Biscuit::IndexBuffer> squareIB;
		squareIB.reset(Biscuit::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5,1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Biscuit::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core		

			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Biscuit::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
		m_TextureColorShader.reset(Biscuit::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Biscuit::Texture2D::Create("assets/texture/Checkerboard.png");
		m_ChernoLogoTexture = Biscuit::Texture2D::Create("assets/texture/ChernoLogo.png");

		std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Biscuit::Timestep ts) override
	{
		//OnUpdata是每一帧都会调用，而Event是只有激活按键时才会响应，所以镜头移动代码放在这里移动会更加丝滑。
		//这里ts计算了屏幕的刷新时间，会根据屏幕刷新去移动，而不受到OnUpdate的频率影响，保证了不同Update下移动速度相同。
		if (Biscuit::Input::IsKeyPressed(BC_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (Biscuit::Input::IsKeyPressed(BC_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Biscuit::Input::IsKeyPressed(BC_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Biscuit::Input::IsKeyPressed(BC_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Biscuit::Input::IsKeyPressed(BC_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		else if(Biscuit::Input::IsKeyPressed(BC_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		Biscuit::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		Biscuit::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Biscuit::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Biscuit::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Biscuit::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		m_Texture->Bind();
		Biscuit::Renderer::Submit(m_TextureColorShader, m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Biscuit::Renderer::Submit(m_TextureColorShader, m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));

		//三角形
		//Biscuit::Renderer::Submit(m_Shader, m_VertexArray);

		Biscuit::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Biscuit::Event& event) override
	{
	}

	bool OnKeyPressedEvent(Biscuit::KeyPressedEvent& event)
	{
	}
private:
	Biscuit::Ref<Biscuit::Shader> m_Shader;
	Biscuit::Ref<Biscuit::Shader> m_FlatColorShader, m_TextureColorShader;
	Biscuit::Ref<Biscuit::VertexArray> m_VertexArray;
	Biscuit::Ref<Biscuit::VertexArray> m_SquareVA;

	Biscuit::Ref<Biscuit::Texture2D> m_Texture, m_ChernoLogoTexture;

	Biscuit::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
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