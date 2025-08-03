#pragma once

#include <Core/Logger.hpp>
#include <GLFW/glfw3.h>

namespace NullEngine
{
	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();
		void Update();
		void Close();

		bool ShouldClose() const;
		bool IsKeyPressed(int key) const;
		bool IsMouseButtonPressed(int button) const;

		void SetTitle(const char* title);
		void SetFullscreen();
		void SetWindowed(int xpos, int ypos, int width, int height);
		void SetVSync(bool enabled) const;

	private:
		Logger m_Logger{ "Window" };
		GLFWwindow* m_Window;
	};
}