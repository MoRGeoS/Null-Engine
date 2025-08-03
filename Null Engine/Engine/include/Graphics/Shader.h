#pragma once

#include <Core/Logger.hpp>

#include <glm/glm.hpp>

namespace NullEngine
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void Use() const;
		void SetBool(const char* name, bool value) const;
		void SetInt(const char* name, int value) const;
		void SetFloat(const char* name, float value) const;
		void SetMat4(const char* name, const glm::mat4& value) const;

		static uint32_t CompileShader(const char* source, uint32_t type);
		static uint32_t LinkProgram(uint32_t vertexShader, uint32_t fragmentShader);

	private:
		uint32_t m_ID;

		static inline Logger m_Logger{ "Shader" };
	};
}