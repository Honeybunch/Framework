#version 330 core

//The color to take in
uniform vec4 inColor;

in vec2 f_uv;

out vec4 color;

void main(void)
{
	color = inColor;
}