#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_Texture;

out vec4 out_Color;
out vec2 out_Texture;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	out_Color = a_Color;
	out_Texture = a_Texture;
}