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
            PushLayer(CreateRef<UnnamedClientApp>(m_Data));
        }

        ~UnnamedClient() {}
    };

    Application* CreateApplication()
    {
        return new UnnamedClient();
    }
}