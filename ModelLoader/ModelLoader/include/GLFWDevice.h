#pragma once
#include <memory>

#include <GLFW/glfw3.h>
#include <memory>

class GLFWDevice
{
public:
	GLFWDevice();
	~GLFWDevice();

	[[nodiscard]] GLFWwindow* GetWindow() const { return m_window; }
	
private:
	GLFWwindow* m_window;
};

