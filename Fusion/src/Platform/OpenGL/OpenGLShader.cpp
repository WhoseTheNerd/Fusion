#include "fpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Fusion { namespace Graphics {

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		uint32_t vertexShader = CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER);
		uint32_t fragmentShader = CompileShader(fragmentSrc.c_str(), GL_FRAGMENT_SHADER);

		m_Program = glCreateProgram();

		glAttachShader(m_Program, vertexShader);
		glAttachShader(m_Program, fragmentShader);

		glLinkProgram(m_Program);

		int linked = 0;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_Program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_Program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			F_CORE_ERROR("{0}", infoLog.data());
			F_CORE_ASSERT(false, "Shader linking failed!");
		}

		glDetachShader(m_Program, vertexShader);
		glDetachShader(m_Program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	uint32_t OpenGLShader::CompileShader(const char* source, const uint32_t type)
	{
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		int compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			F_CORE_ERROR("{0}", infoLog.data());
			F_CORE_ASSERT(false, "Shader compilation failed!");
			return 0;
		}
		return shader;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_Program);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_Program);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(NULL);
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{
		int location = GetUniformLocation(name);
		glProgramUniform1i(m_Program, location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, const int* const values, const uint32_t count)
	{
		int location = GetUniformLocation(name);
		glProgramUniform1iv(m_Program, location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		int location = GetUniformLocation(name);
		glProgramUniform1f(m_Program, location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		int location = GetUniformLocation(name);
		glProgramUniform2f(m_Program, location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		int location = GetUniformLocation(name);
		glProgramUniform3f(m_Program, location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		int location = GetUniformLocation(name);
		glProgramUniform4f(m_Program, location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		int location = GetUniformLocation(name);
		glProgramUniformMatrix4fv(m_Program, location, 1, GL_FALSE, glm::value_ptr(value));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(m_Program, name.c_str());
	}

} }
