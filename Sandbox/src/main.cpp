#include <Fusion.h>

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>

class SandboxLayer : public Fusion::Layer
{
public:
	virtual void OnAttach()
	{
		std::vector<float> vertices = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		std::vector<uint32_t> indices = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Create VBO
		m_VBO = Fusion::Graphics::VertexBuffer::Create(vertices);
		m_VBO->SetLayout({ {Fusion::Graphics::ShaderDataType::Float3, "in_Position"} });
		
		// Create IBO
		m_IBO = Fusion::Graphics::IndexBuffer::Create(indices);

		// Create and configure VAO
		m_VAO = Fusion::Graphics::VertexArray::Create();
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->AddIndexBuffer(m_IBO);
	}

	virtual void OnDetach()
	{
	}

	virtual void OnUpdate(const Fusion::Timestep ts)
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_VAO->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void OnEvent(Fusion::Event& event)
	{

	}
private:
	Fusion::Ref<Fusion::Graphics::VertexArray> m_VAO;
	Fusion::Ref<Fusion::Graphics::VertexBuffer> m_VBO;
	Fusion::Ref<Fusion::Graphics::IndexBuffer> m_IBO;
};

class Sandbox : public Fusion::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

Fusion::Scope<Fusion::Application> Fusion::CreateApplication()
{
	return Fusion::CreateScope<Sandbox>();
}
