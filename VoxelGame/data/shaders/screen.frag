#version 460 core

in vec2 out_Texture;

uniform sampler2D screenTexture;

void main()
{
	vec3 color = texture(screenTexture, out_Texture).rgb;
	gl_FragColor = vec4(color, 1.0);
}