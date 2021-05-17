#include "SandboxLayer.h"

namespace Sandbox {

	SandboxLayer::SandboxLayer()
		: m_Sound("helloworld.wav"), m_Music("Evacuate - Ludum Dare 30.ogg"), m_CameraController(960.0f / 540.0f)
	{
		m_Sound.Play();
		m_Sound.Wait();
		m_Music.Play();
	}

	void SandboxLayer::OnAttach()
	{
		Fusion::Graphics::Renderer2D::Init();

		m_Texture = Fusion::Graphics::Texture2D::Create("wall.jpg");

		Fusion::Graphics::RenderCommand::SetClearColor(Fusion::HexToRGB("334C4C"));
	}
	
	void SandboxLayer::OnDetach()
	{
		Fusion::Graphics::Renderer2D::Shutdown();
	}

	void SandboxLayer::OnUpdate(const Fusion::Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		Fusion::Graphics::RenderCommand::Clear();
		Fusion::Graphics::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Fusion::Graphics::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
		Fusion::Graphics::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.8, 0.3, 0.2, 1.0f });
		Fusion::Graphics::Renderer2D::EndScene();
	}
	
	void SandboxLayer::OnEvent(Fusion::Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}
