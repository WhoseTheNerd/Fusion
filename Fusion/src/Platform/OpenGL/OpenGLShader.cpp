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
		// TODO: Clean up

		const char* vertexSource = vertexSrc.c_str();
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		int compiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			F_CORE_ERROR("{0}", infoLog.data());
			F_CORE_ASSERT(false, "Vertex shader compilation failed!");
		}
		
		const char* fragmentSource = fragmentSrc.c_str();
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		
		compiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			F_CORE_ERROR("{0}", infoLog.data());
			F_CORE_ASSERT(false, "Fragment shader compilation failed!");
		}

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);

		glLinkProgram(m_ShaderProgram);

		int linked = 0;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderProgram, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ShaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			F_CORE_ERROR("{0}", infoLog.data());
			F_CORE_ASSERT(false, "Shader linking failed!");
		}

		glDetachShader(m_ShaderProgram, vertexShader);
		glDetachShader(m_ShaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(NULL);
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, const int* const values, const uint32_t count)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

} }
