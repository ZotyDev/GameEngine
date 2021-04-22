#version 460

in vec2 out_Texture;

uniform sampler2D u_Texture1;

void main()
{
	gl_FragColor = texture(u_Texture1, out_Texture);
}