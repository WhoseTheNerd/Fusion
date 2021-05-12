#pragma once

#include "Fusion/Graphics/Shader.h"

namespace Fusion { namespace Graphics {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetInt(const char* name, const int value) override;
		virtual void SetIntArray(const char* name, const int* const values, const uint32_t count) override;
		virtual void SetFloat(const char* name, float value) override;
		virtual void SetFloat2(const char* name, const glm::vec2& value) override;
		virtual void SetFloat3(const char* name, const glm::vec3& value) override;
		virtual void SetFloat4(const char* name, const glm::vec4& value) override;
		virtual void SetMat4(const char* name, const glm::mat4& value) override;
	private:
		uint32_t CompileShader(const char* source, const uint32_t type);
		int GetUniformLocation(const char* name);
	private:
		uint32_t m_Program;
	};

} }
