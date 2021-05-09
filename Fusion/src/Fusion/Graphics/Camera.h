#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class F_API Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projetion, const glm::mat4& view)
			: m_ProjectionMatrix(projetion), m_ViewMatrix(view)
		{}
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	};

} }
