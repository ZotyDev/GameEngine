#include <UnnamedEngine.hpp>
#include <Core/EntryPoint.hpp>

#include "UnnamedClientApp.hpp"

namespace UE
{
    class UnnamedClient : public Application
	{
	public:
		UnnamedClient()
		{
			PushLayer(CreateRef<UnnamedClientApp>());
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