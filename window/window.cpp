#include "window.h"

GLFWwindow* Window::window;

int Window::Initialize(int width, int heigh, std::string name)
{
  glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	Window::window = glfwCreateWindow(width, heigh, name.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(Window::window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

  return 0;
}

int Window::ShouldClose()
{
  return glfwWindowShouldClose(Window::window);
}

void Window::SwapBuffers()
{
  glfwSwapBuffers(Window::window);
}

void Window::PollEvents()
{
  glfwPollEvents();
}

void Window::Terminate()
{
  glfwTerminate();
}
