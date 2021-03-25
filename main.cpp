#include "shader/shader.h"
#include "window/window.h"
#include "texture/texture.h"

int main(int argc, char **argv)
{
	Window::Initialize(640, 480, "OpenGL lesson 7");
	Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");

	Texture texture("res/textures/texture.png");
	texture.bind();
	shader.uniform1i("slot", 0);

	unsigned int VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,

		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	float vertexUV[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	unsigned int uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertexUV, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	shader.use();


	while (!Window::ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		Window::SwapBuffers();
		Window::PollEvents();
	}

	glUseProgram(0);
	Window::Terminate();
	return 0;
}
