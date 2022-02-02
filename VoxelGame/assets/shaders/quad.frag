#version 460 core

layout (location = 0) out vec4 Color;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) in VertexOutput Input;

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	vec4 TexColor = Input.Color;

	switch(int(Input.TexIndex))
	{
		case 0:
	}
}