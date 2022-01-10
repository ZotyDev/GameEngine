#version 460 core

in vec2 out_Texture;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, out_Texture);
}