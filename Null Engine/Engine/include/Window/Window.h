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
		bool ShouldClose() const;

	private:
		Logger m_Logger{"Window"};
		GLFWwindow* m_Window;
		int m_Width;
		int m_Height;
	};
}