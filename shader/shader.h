#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
private:
  unsigned int id;
  std::string extractSource(const char * file_path);
  unsigned int compileShader(unsigned int type, std::string &source);
  unsigned int loadShader(std::string vertexFile, std::string fragmentFile);

public:
  Shader(std::string vertexFile, std::string fragmentFile);
  void uniform4f(std::string name, float a, float b, float c, float d);
  void uniform1i(std::string name, int a);
  void use();
};
