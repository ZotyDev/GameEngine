#version 460 core

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

void main()
{
	gl_Position = u_ViewProjection * (u_Transform * vec4(v_Position, 1.0));
	Texture = v_Texture;
}