#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "UnnamedClientApp.h"

namespace UE
{
	class UnnamedClient : public Application
	{
	public:
		UnnamedClient()
		{
			PushLayer(CreateRef<UnnamedClientApp>(m_Data));
		}

		~UnnamedClient()
		{

		}
	};

	Application* CreateApplication()
	{
		return new UnnamedClient();
	}
}