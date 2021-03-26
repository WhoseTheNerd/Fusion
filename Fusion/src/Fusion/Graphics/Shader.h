#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class Shader
	{
	public:
		virtual ~Shader() = default;
	
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt(const std::string& name, const int value) = 0;
		virtual void SetIntArray(const std::string& name, const int* const values, const uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, const float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

} }