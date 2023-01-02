#include "uepch.h"
#include "World/ChunkMesher.h"

#include "Renderer/Primitives.h"

/*
*        4 #--------# 6
*         /|       /|
*        / |      / |
*     0 #--+-----# 2|
*       |5 #-----|--# 7
*       | /      | /
*       |/       |/
*     1 #--------# 3
* 
*/

namespace UE
{
	#define Vert1  0.5f, -0.5f,  0.5f, 0.0f, 1.0f
	#define Vert2 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f
	#define Vert3  0.5f,  0.5f,  0.5f, 1.0f, 0.0f
	#define Vert4 -0.5f,  0.5f,  0.5f, 1.0f, 1.0f
	#define Vert5 -0.5f, -0.5f, -0.5f, 1.0f, 0.0f
	#define Vert6  0.5f, -0.5f, -0.5f, 0.0f, 0.0f
	#define Vert7 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	#define Vert8  0.5f,  0.5f, -0.5f, 1.0f, 1.0f

	void AddFace(UEUint32 x, UEUint32 y, UEUint32 z, UEUint32 face)
	{

	}

	Ref<VertexArray> ChunkMesher::Bake(Ref<Chunk> chunk)
	{
		Ref<VertexBuffer> t_VBuffer;
		Ref<IndexBuffer> t_IBuffer;
		Ref<VertexArray> t_VAO = VertexArray::Create();

		std::vector<UEFloat> ChunkVertices;
		std::vector<UEUint32> ChunkIndices;

		UEUint32 IndiceCounter = 0;
		for (UEUint32 x = 0; x < 4; x++)
		{
			for (UEUint32 y = 0; y < CHUNK_SIZE; y++)
			{
				for (UEUint32 z = 0; z < CHUNK_SIZE; z++)
				{
				}
			}
		}
		
		//   X     Y     Z    F
		// 
		// 11111 11111 11111 111

		UEUint32 VertData = 1 | 1 << 5 | 1 << 10 | 0 << 15;


		ChunkVertices.insert(ChunkVertices.end(), {
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f
			});

		ChunkIndices = {
			0, 2, 1, 1, 2, 3,
			6, 4, 7, 7, 4, 5,
			4, 0, 5, 5, 0, 1,
			2, 6, 3, 3, 6, 7,
			4, 6, 0, 0, 6, 2,
			1, 3, 5, 5, 3, 7
		};

		Primitives::Quad t_Quad({ -0.5f, 0.5f }, { 0.5f, -0.5f });

		t_VBuffer = VertexBuffer::Create(ChunkVertices.data(), sizeof(UEFloat) * ChunkVertices.size());

		BufferLayout Layout =
		{
			{ ShaderDataType::Vec3, "vi_Position" },
			{ ShaderDataType::Vec2, "vi_Texture" },
		};

		t_VBuffer->SetLayout(Layout);
		t_VAO->AddVertexBuffer(t_VBuffer);

		t_IBuffer = IndexBuffer::Create(ChunkIndices.data(), ChunkIndices.size());
		t_VAO->AddIndexBuffer(t_IBuffer);

		chunk->m_Mesh = t_VAO;

		return t_VAO;
	}
}