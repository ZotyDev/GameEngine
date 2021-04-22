#version 460 core

in vec2 out_Texture;

uniform sampler2D u_ScreenTexture;

void main()
{
	vec3 color = texture(u_ScreenTexture, out_Texture).rgb;
	gl_FragColor = vec4(color, 1.0);
}