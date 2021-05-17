#pragma once

#include <Fusion.h>

namespace Sandbox {

	class SandboxLayer : public Fusion::Layer
	{
	public:
		SandboxLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const Fusion::Timestep ts) override;
		virtual void OnEvent(Fusion::Event& event) override;
	private:
		Fusion::Ref<Fusion::Graphics::Texture2D> m_Texture;
		Fusion::Graphics::OrthographicCameraController m_CameraController;

		Fusion::Audio::System m_AudioSystem;
		Fusion::Audio::Music m_Music;
		Fusion::Audio::Sound m_Sound;
	};
}
