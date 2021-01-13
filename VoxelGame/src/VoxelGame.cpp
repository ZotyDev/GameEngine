#include <UnnamedEngine.h>

class VoxelGame : public UE::Application
{
public:
	VoxelGame()
	{

	}

	~VoxelGame()
	{

	}
};

UE::Application* UE::CreateApplication()
{
	return new VoxelGame();
}