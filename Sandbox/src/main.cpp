#define F_MAIN_APP
#include <Fusion.h>

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
