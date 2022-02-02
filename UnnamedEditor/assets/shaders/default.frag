#version 460 core

void main()
{
	float ambient = 1.0;
	vec3 Color = texture(us_Albedo, fi_Texture).rgb;
	vec3 Lighting = vec3(ambient);
	fo_FragColor = vec4(Color * Lighting, 1.0);
}