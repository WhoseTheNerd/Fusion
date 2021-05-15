#include "fpch.h"
#include "Listener.hpp"

#include <al.h>

namespace Fusion { namespace Audio {

	void Listener::SetPosition(float x, float y, float z)
	{
		alListener3f(AL_POSITION, x, y, z);
	}

	void Listener::SetVelocity(float x, float y, float z)
	{
		alListener3f(AL_VELOCITY, x, y, z);
	}

	void Listener::SetOrientation(const std::array<float, 6>& orientation)
	{
		alListenerfv(AL_ORIENTATION, &orientation[0]);
	}
} }
