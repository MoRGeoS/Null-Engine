#include <glad/glad.h>

#include <Engine.h>

#include <Utils/Path.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::vec3 vertexData[] = {
	{ -0.5f, -0.5f, 0.0f },
	{  0.5f, -0.5f, 0.0f },
	{  0.0f,  0.5f, 0.0f }
};

uint32_t indexData[] = {
	0, 1, 2
};

namespace NullEngine
{
	Engine::Engine()
		: m_Logger(std::make_unique<Logger>("Engine"))
	{
		m_Logger->Info("Engine initializing...");

		SetCurrentDirectoryToExeDir();

		if (!glfwInit())
		{
			m_Logger->ThrowError("Failed to initialize GLFW");
		}
		m_Logger->Info("GLFW initialized.");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = std::make_unique<Window>(800, 600, "Null Engine");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			m_Logger->ThrowError("Failed to initialize GLAD");
		}
		m_Logger->Info("GLAD initialized.");

		m_Logger->PrintEmptyLine();
		m_Logger->Info("OpenGL Information:\n[Vendor]: {}\n[Renderer]: {}\n[Version]: {}\n[Shading Language Version]: {}",
			std::string(reinterpret_cast<const char*>(glad_glGetString(GL_VENDOR))),
			std::string(reinterpret_cast<const char*>(glad_glGetString(GL_RENDERER))),
			std::string(reinterpret_cast<const char*>(glad_glGetString(GL_VERSION))),
			std::string(reinterpret_cast<const char*>(glad_glGetString(GL_SHADING_LANGUAGE_VERSION)))
		);
		m_Logger->PrintEmptyLine();

		m_Shader = std::make_unique<Shader>("vertex.glsl", "fragment.glsl");
		m_Mesh = std::make_unique<Mesh>(vertexData, sizeof(vertexData) / sizeof(vertexData[0]), indexData, sizeof(indexData) / sizeof(indexData[0]));

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		m_ModelMatrix = glm::mat4(1.0f);

		m_Logger->Info("Engine initialized.");
	}

	Engine::~Engine()
	{
		m_Logger->PrintEmptyLine();
		m_Logger->Info("Shutting down Engine...");
		m_Logger->Info("Engine shutdown complete.");

		glfwTerminate();
		m_Logger->Info("GLFW terminated.");
	}

	void Engine::Run()
	{
		m_Logger->Info("Starting Engine...");
		m_Window->SetVSync(false);

		while (!m_Window->ShouldClose())
		{
			m_Window->Update();
			if (m_Window->IsKeyPressed(GLFW_KEY_ESCAPE))
			{
				m_Logger->Info("Key \'Esc\' pressed, closing window.");
				m_Window->Close();
			}

			m_Shader->Use();
			m_Shader->SetMat4("projection", m_ProjectionMatrix);
			m_Shader->SetMat4("view", m_ViewMatrix);
			m_Shader->SetMat4("model", m_ModelMatrix);
			m_Mesh->Draw();
		}

		m_Logger->Info("Engine stopped.");
	}
}