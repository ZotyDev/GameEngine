#version 460 core

void main()
{
	gl_FragColor = vec4(gl_FragCoord.z);
}