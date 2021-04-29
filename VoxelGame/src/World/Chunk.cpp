#include "uepch.h"
#include "Chunk.h"

Chunk::Chunk()
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		m_BlockArray[i] = Block(1);
	}
}