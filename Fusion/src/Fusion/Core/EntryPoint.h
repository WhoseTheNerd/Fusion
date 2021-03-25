#pragma once

#ifdef F_PLATFORM_WINDOWS

extern Fusion::Scope<Fusion::Application> Fusion::CreateApplication();

#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
	Fusion::Log::Init();

	F_CORE_INFO("Initializing Application");
	auto app = Fusion::CreateApplication();
	app->Run();
}

#else
#error Fusion supports Windows right now
#endif
