#include <Fusion.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SandboxLayer.h"

class SandboxApp : public Fusion::Application
{
public:
	SandboxApp()
	{
		PushLayer(Fusion::CreateRef<Sandbox::SandboxLayer>());
	}
};

Fusion::Scope<Fusion::Application> Fusion::CreateApplication()
{
	return Fusion::CreateScope<SandboxApp>();
}
