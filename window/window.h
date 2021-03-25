#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window
{
private:
  static GLFWwindow* window;

public:
  static int Initialize(int width, int heigh, std::string name);
  static int ShouldClose();
  static void SwapBuffers();
  static void PollEvents();
  static void Terminate();
};
