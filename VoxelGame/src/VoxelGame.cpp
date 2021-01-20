#include <UnnamedEngine.h>

#include <iostream>

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