#include <Fusion.h>

#include <glad/glad.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public Fusion::Layer
{
public:
	SandboxLayer()
		: m_Sound("helloworld.wav"), m_Music("Evacuate - Ludum Dare 30.ogg")
	{
		m_Sound.Play();
		m_Sound.Wait();
		m_Music.Play();
	}

	virtual void OnAttach()
	{
		Fusion::Graphics::Renderer2D::Init();

		m_Texture = Fusion::Graphics::Texture2D::Create("wall.jpg");

		Fusion::Graphics::RenderCommand::SetClearColor(Fusion::HexToRGB("334C4C"));
	}

	virtual void OnDetach()
	{
		Fusion::Graphics::Renderer2D::Shutdown();
	}

	virtual void OnUpdate(const Fusion::Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		Fusion::Graphics::RenderCommand::Clear();
		Fusion::Graphics::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fusion::Graphics::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
		Fusion::Graphics::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.8, 0.3, 0.2, 1.0f });
		Fusion::Graphics::Renderer2D::EndScene();
	}

	virtual void OnEvent(Fusion::Event& event)
	{
		m_CameraController.OnEvent(event);
	}
private:
	Fusion::Ref<Fusion::Graphics::Texture2D> m_Texture;
	Fusion::Graphics::OrthographicCameraController m_CameraController{ 960.0f / 540.0f };

	Fusion::Audio::System m_AudioSystem;
	Fusion::Audio::Music m_Music;
	Fusion::Audio::Sound m_Sound;
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
