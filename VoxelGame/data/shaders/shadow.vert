#version 460 core
layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform vec3 u_Position;

void main()
{
	gl_Position = u_ViewProjection * (vec4(a_Position, 1.0) + vec4(u_Position, 1.0));
}