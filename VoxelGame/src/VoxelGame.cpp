#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "VoxelGameApp.h"

class VoxelGame : public UE::Application
{
public:
	VoxelGame()
	{
		PushLayer(new VoxelGameApp(UE::CreateRef<UE::Application::SharedData>(m_Data)));
	}

	~VoxelGame()
	{

	}
};

UE::Application* UE::CreateApplication()
{
	return new VoxelGame();
}