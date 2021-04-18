#version 460

in vec4 out_Color;
in vec2 out_Texture;

uniform sampler2D ourTexture;

void main()
{
	gl_FragColor = texture(ourTexture, out_Texture);
}