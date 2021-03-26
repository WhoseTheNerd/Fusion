#include <Fusion.h>

#include <glad/glad.h>

class SandboxLayer : public Fusion::Layer
{
public:
	virtual void OnAttach()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Create VBO
		glCreateBuffers(1, &vbo);
		glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		// Create IBO
		glCreateBuffers(1, &ibo);
		glNamedBufferData(ibo, sizeof(indices), indices, GL_STATIC_DRAW);

		// Create and configure VAO
		glCreateVertexArrays(1, &vao); 
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);
		glVertexArrayElementBuffer(vao, ibo);
		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, NULL);
	}

	virtual void OnDetach()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
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
	uint32_t vbo;
	uint32_t ibo;
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
