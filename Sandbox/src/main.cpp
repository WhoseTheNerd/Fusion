#include <Fusion.h>

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public Fusion::Layer
{
public:
	virtual void OnAttach()
	{
		std::vector<float> vertices = {
			// Vertex position     Texture coords
			 0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,	   0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,	   0.0f, 1.0f,
		};

		std::vector<uint32_t> indices = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Create VBO
		m_VBO = Fusion::Graphics::VertexBuffer::Create(vertices);
		m_VBO->SetLayout({ 
			{Fusion::Graphics::ShaderDataType::Float3, "in_Position"},
			{Fusion::Graphics::ShaderDataType::Float2, "in_TexCoords"}
		});
		
		// Create IBO
		m_IBO = Fusion::Graphics::IndexBuffer::Create(indices);

		// Create and configure VAO
		m_VAO = Fusion::Graphics::VertexArray::Create();
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->AddIndexBuffer(m_IBO);

		m_Texture = Fusion::Graphics::Texture2D::Create("wall.jpg");

		std::string vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 0) in vec2 in_TexCoords;
out vec2 out_TexCoords;
uniform mat4 u_Transform = mat4(1.0);
void main()
{
	out_TexCoords = in_TexCoords;
	gl_Position = vec4(in_Position, 1.0) * u_Transform;
}		
)";

		std::string fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
in vec2 out_TexCoords;
uniform sampler2D u_Texture;
void main()
{
	FragColor = texture(u_Texture, out_TexCoords);
}		
)";

		m_Shader = Fusion::Graphics::Shader::Create(vertexShaderSrc, fragmentShaderSrc);
		m_Shader->SetInt("u_Texture", 0);

		m_TransformMatrix = glm::mat4(1.0f);
		m_TransformMatrix = glm::translate(m_TransformMatrix, { 0.0f, 0.0f, 0.0f });
		m_TransformMatrix = glm::rotate(m_TransformMatrix, glm::radians(0.0f), { 0.0f, 0.0f, 1.0f });
		m_TransformMatrix = glm::scale(m_TransformMatrix, glm::vec3(1.0f));
		m_Shader->SetMat4("u_Transform", m_TransformMatrix);
	}

	virtual void OnDetach()
	{
	}

	virtual void OnUpdate(const Fusion::Timestep ts)
	{
		Fusion::Graphics::RenderCommand::SetClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		Fusion::Graphics::RenderCommand::Clear();

		m_VAO->Bind();
		m_Shader->Bind();
		m_Texture->Bind();
		Fusion::Graphics::RenderCommand::DrawIndexed(m_VAO);
	}

	virtual void OnEvent(Fusion::Event& event)
	{

	}
private:
	Fusion::Ref<Fusion::Graphics::VertexArray> m_VAO;
	Fusion::Ref<Fusion::Graphics::VertexBuffer> m_VBO;
	Fusion::Ref<Fusion::Graphics::IndexBuffer> m_IBO;
	Fusion::Ref<Fusion::Graphics::Shader> m_Shader;
	Fusion::Ref<Fusion::Graphics::Texture2D> m_Texture;
	glm::mat4 m_TransformMatrix;
};

class Sandbox : public Fusion::Application
{
public:
	Sandbox()
	{
		PushLayer(Fusion::CreateRef<SandboxLayer>());
	}

	~Sandbox()
	{

	}
};

Fusion::Scope<Fusion::Application> Fusion::CreateApplication()
{
	return Fusion::CreateScope<Sandbox>();
}
