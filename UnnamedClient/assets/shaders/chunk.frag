#version 460 core

void main()
{
	vec4 Color = texture(us_Albedo, fi_Texture);
	fo_FragColor = Color;
}