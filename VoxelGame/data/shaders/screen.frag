#version 460 core

in vec2 out_Texture;

uniform sampler2D u_ScreenTexture;

float gamma = 1.0;

void main()
{
	vec3 color = texture(u_ScreenTexture, out_Texture).rgb;
	gl_FragColor = pow(vec4(color, 1.0), vec4(1.0f / gamma));
}