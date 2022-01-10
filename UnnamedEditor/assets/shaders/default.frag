#version 460 core

layout (binding = 0) uniform sampler2D u_Texture1;

void main()
{
	float ambient = 1.0;
	vec3 Color = texture(u_Texture1, Texture).rgb;
	vec3 Lighting = vec3(ambient);
	FragColor = vec4(Color * Lighting, 1.0);
}