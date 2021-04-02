#include "shader.h"

std::string Shader::extractSource(const char * file_path)
{
	std::string ShaderCode;
	std::ifstream ShaderStream(file_path, std::ios::in);
	if(ShaderStream.is_open()){

		std::string Line = "";
		while(getline(ShaderStream, Line))
		{
			ShaderCode += "\n" + Line;
		}
		ShaderStream.close();
	}

	return ShaderCode;
}

unsigned int Shader::compileShader(unsigned int type, std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout <<"\t"<< message << std::endl;

		glDeleteShader(id);
		delete[] message;

		return 0;
	}

	return id;
}


unsigned int Shader::loadShader(std::string vertexFile, std::string fragmentFile) {

	unsigned int id = glCreateProgram();

	std::string vsCode = extractSource(vertexFile.c_str());
	std::string fsCode = extractSource(fragmentFile.c_str());

	unsigned int vs = compileShader(GL_VERTEX_SHADER, vsCode);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsCode);

	glAttachShader(id, vs);
	glAttachShader(id, fs);

	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return id;
}

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
  this->id = this->loadShader(vertexFile, fragmentFile);
}

void Shader::uniform4f(std::string name, float a, float b, float c, float d)
{
  unsigned int u_loc = glGetUniformLocation(this->id, name.c_str());
  glUniform4f(u_loc, a, b, c, d);
}

void Shader::uniform1i(std::string name, int a)
{
	unsigned int u_loc = glGetUniformLocation(this->id, name.c_str());
	glUniform1i(u_loc, a);
}

void Shader::uniformMatrix4f(std::string name, glm::mat4 mat)
{
	unsigned int u_loc = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(u_loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::use()
{
  glUseProgram(this->id);
}
