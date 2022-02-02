#include "uepch.h"
#include "World/ChunkMesher.h"

namespace UE
{
	Ref<VertexArray> ChunkMesher::Bake(Ref<Chunk> chunk)
	{
		for (UEUint32 x = 0; x < CHUNK_SIZE; x++)
		{
			for (UEUint32 y = 0; y < CHUNK_SIZE; y++)
			{
				for (UEUint32 z = 0; z < CHUNK_SIZE; z++)
				{

				}
			}
		}

		return nullptr;
	}
}