#include <Graphics/Shader.h>

#include <Utils/FileIO.hpp>

#include <glad/glad.h>

namespace NullEngine
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode = FileIO::ReadFile(vertexPath);
		std::string fragmentCode = FileIO::ReadFile(fragmentPath);

		uint32_t vertexShader = CompileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
		uint32_t fragmentShader = CompileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
		
		m_ID = LinkProgram(vertexShader, fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}



	void Shader::Use() const
	{
		glUseProgram(m_ID);
	}
	void Shader::SetBool(const char* name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name), static_cast<int>(value));
	}
	void Shader::SetInt(const char* name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name), value);
	}
	void Shader::SetFloat(const char* name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name), value);
	}
	void Shader::SetMat4(const char* name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &value[0][0]);
	}



	uint32_t Shader::CompileShader(const char* source, uint32_t type)
	{
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			m_Logger.ThrowError("Shader compilation failed: {}", infoLog);
		}
		return shader;
	}
	uint32_t Shader::LinkProgram(uint32_t vertexShader, uint32_t fragmentShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			m_Logger.ThrowError("Program linking failed: {}", infoLog);
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return program;
	}
}