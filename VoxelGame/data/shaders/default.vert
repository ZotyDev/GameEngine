#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_Texture;

out vec2 out_Texture;

uniform mat4 u_ViewProjection;
uniform vec3 u_Position;

uniform mat4 u_LightViewProjection;
out vec4 out_FragPositionLightSpace;

void main()
{
	gl_Position = u_ViewProjection * (vec4(a_Position, 1.0) + vec4(u_Position, 1.0));
	out_Texture = a_Texture;

	out_FragPositionLightSpace = u_LightViewProjection * (vec4(a_Position, 1.0) + vec4(u_Position, 1.0));
}