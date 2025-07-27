#include <Window/Window.h>

namespace NullEngine
{
	Window::Window(int width, int height, const char* title)
		: m_Width(width), m_Height(height)
	{
		if (!glfwInit())
		{
			m_Logger.ThrowError("Failed to initialize GLFW");
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr);
		if (!m_Window)
		{
			glfwTerminate();
			m_Logger.ThrowError("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(m_Window);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Window);
	}
}