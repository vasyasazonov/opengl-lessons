#pragma once
#include <string>
#include <GL/glew.h>

class Texture
{
private:
  unsigned int id;
  std::string filePath;
  unsigned char *buffer;
  int width, height, bpp;
public:
  Texture(const std::string filePath);
  ~Texture();

  void bind(unsigned int slot = 0);
  void unbind();
};
