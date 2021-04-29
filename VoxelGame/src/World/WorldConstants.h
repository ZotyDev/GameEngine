#pragma once

#define CHUNK_SIZE		16
#define CHUNK_AREA		(CHUNK_SIZE * CHUNK_SIZE)
#define CHUNK_VOLUME	(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)

struct ChunkPos
{
	int X;
	int Y;
	int Z;

	bool operator==(const ChunkPos& other) const
	{
		return(X == other.X && Y == other.Y && Z == other.Z);
	}
};

class Block
{
public:
	Block()
		: Type(0)
	{}

	Block(int type)
		: Type(type)
	{}

	int Type;
};

// ChunkPos hashable function
namespace std
{
	template<>
	struct hash<ChunkPos>
	{
		std::size_t operator()(const ChunkPos& cc) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<int>()(cc.X) ^ (hash<int>()(cc.Y) << 1)) >> 1) ^ (hash<int>()(cc.Z) << 1);
		}
	};
}