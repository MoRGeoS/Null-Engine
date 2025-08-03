#include <Graphics/Window.h>

namespace NullEngine
{
	Window::Window(int width, int height, const char* title)
	{
		if (!glfwInit())
		{
			m_Logger.ThrowError("Failed to initialize GLFW");
		}
		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}



	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Window);
	}
	bool Window::IsKeyPressed(int key) const
	{
		return glfwGetKey(m_Window, key);
	}
	bool Window::IsMouseButtonPressed(int button) const
	{
		return glfwGetMouseButton(m_Window, button);
	}



	void Window::SetTitle(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
		m_Logger.Info("Window title set to: {}", title);
	}
	void Window::SetFullscreen()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (monitor)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			m_Logger.Info("Window set to fullscreen mode.");
		}
		else
		{
			m_Logger.Warning("No primary monitor found, cannot set fullscreen.");
		}
	}
	void Window::SetWindowed(int xpos, int ypos, int width, int height)
	{
		glfwSetWindowMonitor(m_Window, nullptr, xpos, ypos, width, height, 0);
		m_Logger.Info("Window set to windowed mode with size: {}x{}", width, height);
	}
	void Window::SetVSync(bool enabled) const
	{
		glfwSwapInterval(enabled ? 1 : 0);
		m_Logger.Info("VSync {}", enabled ? "enabled" : "disabled");
	}
}