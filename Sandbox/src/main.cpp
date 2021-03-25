#include <Fusion.h>

class Sandbox : public Fusion::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Fusion::Scope<Fusion::Application> Fusion::CreateApplication()
{
	return Fusion::CreateScope<Sandbox>();
}
