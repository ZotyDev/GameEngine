#include "uepch.h"
#include "World/Chunk.h"

namespace UE
{
	Chunk::Chunk()
	{
		Clear();
	}

	void Chunk::Clear()
	{
		for (UEUint32 i = 0; i < CHUNK_VOLUME; i++)
		{
			Voxels[i] = 0;
		}
	}

	ChunkManager::ChunkManager()
	{}

	void ChunkManager::AddChunk(const glm::ivec3& pos)
	{
		auto it = m_Chunks.find(pos);
		auto end = m_Chunks.end();
		if (it != end)
		{
			UE_ERROR("Failed to add Chunk at x: {0} y: {1} z: {2}: position already taken", pos.x, pos.y, pos.z);
			return;
		}

		m_Chunks.insert({ pos, CreateRef<Chunk>() });
	}

	Ref<Chunk> ChunkManager::GetChunk(const glm::ivec3& pos)
	{
		auto it = m_Chunks.find(pos);
		auto end = m_Chunks.end();
		if (it == end)
		{
			UE_ERROR("Failed to get Chunk at x: {0} y: {1} z: {2}: position is empty", pos.x, pos.y, pos.z);
			return nullptr;
		}

		return it->second;
	}
}