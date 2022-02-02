#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "VoxelGameApp.h"

namespace UE
{
	class VoxelGame : public Application
	{
	public:
		VoxelGame()
		{
			PushLayer(new VoxelGameApp(m_Data));
		}

		~VoxelGame()
		{

		}
	};

	Application* CreateApplication()
	{
		return new VoxelGame();
	}
}