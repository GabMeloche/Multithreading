#include <GLFWDevice.h>

GLFWDevice::GLFWDevice()
{
	glfwInit();
	m_window = std::make_unique<GLFWwindow>(1024, 768);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// OpenGL Context configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
