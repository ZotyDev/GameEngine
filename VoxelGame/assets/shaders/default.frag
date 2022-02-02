#version 460 core

void main()
{
	vec4 Color = texture(us_Albedo, fi_Texture);
	//if (Color.a < 0.1)
	//{
	//	//Color = vec4(1.0f);
	//	discard;
	//}
	fo_FragColor = Color;
}