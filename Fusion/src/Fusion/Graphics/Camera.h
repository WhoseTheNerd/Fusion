#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projetion)
			: m_ProjectionMatrix(projetion) 
		{}
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};

} }
