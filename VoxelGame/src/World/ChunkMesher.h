#pragma once

#include "World/Chunk.h"

#include "Renderer/VertexArray.h"

namespace UE
{
	class ChunkMesher
	{
	public:

		static Ref<VertexArray> Bake(Ref<Chunk> chunk);

	private:
	};
}