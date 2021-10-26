#version 460 core

in vec2 out_Texture;

uniform sampler2D u_Texture1;
uniform sampler2D u_ShadowMap;

in vec4 out_FragPositionLightSpace;

out vec4 FragColor;

float ShadowCalculation(vec4 fragPositionLightSpace)
{
	vec3 projCoords = fragPositionLightSpace.xyz / fragPositionLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(u_ShadowMap, projCoords.xy).r;

	float currentDepth = projCoords.z;

	float bias = 0.005;
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	if(projCoords.z > 1.0)
	{
		shadow = 0.0;
	}

	return shadow;
}

void main()
{
	float ambient = 0.2;
	vec3 Color = texture(u_Texture1, out_Texture).rgb;
	vec3 Lighting = vec3(ambient + (1.0 - ShadowCalculation(out_FragPositionLightSpace)));
	FragColor = vec4(Color * Lighting, 1.0);
}