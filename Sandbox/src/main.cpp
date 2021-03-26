#include <Fusion.h>

#include <glad/glad.h>

#include <vector>

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
		
		// Create IBO
		m_IBO = Fusion::Graphics::IndexBuffer::Create(indices);

		// Create and configure VAO
		glCreateVertexArrays(1, &vao); 
		glVertexArrayVertexBuffer(vao, 0, m_VBO->GetBufferHandle(), 0, sizeof(float) * 3);
		glVertexArrayElementBuffer(vao, m_IBO->GetBufferHandle());
		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, NULL);
	}

	virtual void OnDetach()
	{
		glDeleteVertexArrays(1, &vao);
	}

	virtual void OnUpdate(Fusion::Timestep ts)
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void OnEvent(Fusion::Event& event)
	{

	}
private:
	uint32_t vao;
	Fusion::Scope<Fusion::Graphics::VertexBuffer> m_VBO;
	Fusion::Scope<Fusion::Graphics::IndexBuffer> m_IBO;
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
