#version 460 core

layout (location = 0) out vec4 FragColor;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;

void main()
{
	if (Input.Color.a == 0.0)
	{
		discard;
	}

	FragColor = Input.Color;
}