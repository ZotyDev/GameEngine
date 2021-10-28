#version 460 core

in vec2 out_Texture;

uniform sampler2D u_Texture1;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Texture1, out_Texture);
}