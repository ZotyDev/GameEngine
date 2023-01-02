#version 460 core

in vec2 out_Texture;

float gamma = 1.0;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D u_ScreenTexture;

void main()
{
	vec3 color = texture(u_ScreenTexture, out_Texture).rgb;
	FragColor = pow(vec4(color, 1.0), vec4(1.0f / gamma));
}