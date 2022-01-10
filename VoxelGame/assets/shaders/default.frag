#version 460 core

in vec2 out_Texture;

in vec4 out_FragPositionLightSpace;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D u_Texture1;

void main()
{
	float ambient = 1.0;
	vec3 Color = texture(u_Texture1, out_Texture).rgb;
	vec3 Lighting = vec3(ambient);
	FragColor = vec4(Color * Lighting, 1.0);
}