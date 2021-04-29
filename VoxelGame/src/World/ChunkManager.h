#pragma once

#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager() = default;

	void AddChunk(ChunkPos position);

private:
	std::unordered_map<ChunkPos, Chunk*> m_ChunkList;
};