#pragma once

#include <Core/Logger.hpp>
#include <Graphics/Window.h>
#include <Graphics/Shader.h>
#include <Graphics/Mesh.h>

#include <memory>

namespace NullEngine
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		void Run();

	private:
		std::unique_ptr<Logger> m_Logger;
		std::unique_ptr<Window> m_Window;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Mesh> m_Mesh;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;
	};
}