#include <GLFWDevice.h>
#include <GLFW/glfw3.h>

GLFWDevice::GLFWDevice()
{
	glfwInit();
	//GLFWWindow* window = glfwCreateWindow(1024, 768, "ModelLoader", NULL, NULL);
	m_window = glfwCreateWindow(1024, 768, "ModelLoader", NULL, NULL);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// OpenGL Context configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
}

GLFWDevice::~GLFWDevice()
{
	glfwDestroyWindow(m_window);
}