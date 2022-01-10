#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_Texture;

out vec2 out_Texture;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

uniform mat4 u_Transform;

uniform mat4 u_LightViewProjection;

out vec4 out_FragPositionLightSpace;

void main()
{
	gl_Position = u_ViewProjection * (u_Transform * vec4(a_Position, 1.0));
	out_Texture = a_Texture;

	out_FragPositionLightSpace = u_LightViewProjection * (u_Transform * vec4(a_Position, 1.0));
}