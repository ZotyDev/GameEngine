#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_Texture;

out vec2 out_Texture;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
	out_Texture = a_Texture;
}