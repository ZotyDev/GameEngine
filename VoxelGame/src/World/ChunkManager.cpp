#include "uepch.h"
#include "ChunkManager.h"

void ChunkManager::AddChunk(ChunkPos position)
{
	auto t_Chunk = new Chunk();
	m_ChunkList.insert({ position, t_Chunk });
}