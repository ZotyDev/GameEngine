#pragma once

#define CHUNK_SIZE		32
#define CHUNK_AREA		CHUNK_SIZE * CHUNK_SIZE
#define CHUNK_VOLUME	CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

#include "World/Voxel.h"

#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"

namespace UE
{
	class Chunk
	{
	public:
		Chunk();

		void Clear();

		Voxel GetVoxel(UEInt32 x, UEInt32 y, UEInt32 z) { return Voxels[z * CHUNK_AREA + y * CHUNK_SIZE + x]; }
		void SetVoxel(UEInt32 x, UEInt32 y, UEInt32 z, Voxel voxel) { Voxels[z * CHUNK_AREA + y * CHUNK_SIZE + x] = voxel; }

		Voxel Voxels[CHUNK_VOLUME];
	};

	class ChunkManager
	{
	public:
		ChunkManager();

		void AddChunk(const glm::ivec3& pos);
		Ref<Chunk> GetChunk(const glm::ivec3& pos);

	private:
		std::unordered_map<glm::ivec3, Ref<Chunk>> m_Chunks;
	};	
}