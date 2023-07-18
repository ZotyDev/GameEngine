#include <UnnamedEngine.hpp>
#include <Core/EntryPoint.hpp>

#include "UnnamedClientApp.hpp"

namespace UE
{
    class UnnamedClient : public Application
	{
	public:
		UnnamedClient(const EntryArgs& args)
			: Application(args)
		{
			PushLayer(CreateRef<UnnamedClientApp>());
		}

		~UnnamedClient()
		{

		}
	};

	Application* CreateApplication(const EntryArgs& args)
	{
		return new UnnamedClient(args);
	}
}