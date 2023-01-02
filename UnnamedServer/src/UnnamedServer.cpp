#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "ServerLayer.h"

namespace UE
{
	class UnnamedServer : public Application
	{
	public:
		UnnamedServer()
		{
			PushLayer(CreateRef<ServerLayer>(m_Data));
		}

		~UnnamedServer()
		{

		}
	};

	Application* CreateApplication()
	{
		return new UnnamedServer();
	}
}