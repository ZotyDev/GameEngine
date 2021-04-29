#pragma once

#include "WorldConstants.h"

class Chunk
{
public:
	Chunk();

	Block m_BlockArray[CHUNK_VOLUME];
};
