#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "VoxelGameApp.h"

class VoxelGame : public UE::Application
{
public:
	VoxelGame()
	{
		PushLayer(new VoxelGameApp());
	}

	~VoxelGame()
	{

	}
};

UE::Application* UE::CreateApplication()
{
	return new VoxelGame();
}