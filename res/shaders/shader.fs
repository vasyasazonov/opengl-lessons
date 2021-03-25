#version 330 core

out vec4 result;

uniform sampler2D slot;
in vec2 uv;

void main()
{
	result = texture(slot, uv);
}
