#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

Texture::Texture(const std::string filePath) : filePath(filePath), id(0), height(0), width(0), bpp(0)
{
  stbi_set_flip_vertically_on_load(1);
  this->buffer = stbi_load(this->filePath.c_str(), &width, &height, &bpp, 4);

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->buffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (this->buffer)
  {
    stbi_image_free(this->buffer);
  }
}

Texture::~Texture()
{
  glDeleteTextures(1, &this->id);
}

void Texture::bind(unsigned int slot /* = 0*/)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
