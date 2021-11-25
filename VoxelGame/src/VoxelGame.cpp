#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "VoxelGameApp.h"

class VoxelGame : public UE::Application
{
public:
	VoxelGame()
	{
		PushLayer(new VoxelGameApp(m_Window, m_Lune, &m_Running, &m_Minimized));
	}

	~VoxelGame()
	{

	}
};

UE::Application* UE::CreateApplication()
{
	return new VoxelGame();
}