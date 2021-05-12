#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class F_API Shader
	{
	public:
		virtual ~Shader() = default;
	
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt(const char* name, const int value) = 0;
		virtual void SetIntArray(const char* name, const int* const values, const uint32_t count) = 0;
		virtual void SetFloat(const char* name, const float value) = 0;
		virtual void SetFloat2(const char* name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const char* name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const char* name, const glm::vec4& value) = 0;
		virtual void SetMat4(const char* name, const glm::mat4& value) = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

} }
