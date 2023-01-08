#include "UnnamedClientApp.hpp"

namespace UE
{
    UnnamedClientApp::UnnamedClientApp(Ref<Application::SharedData> data)
        : Layer("UnnamedClient"), m_Data(data)
    {}

    void UnnamedClientApp::OnAttach()
    {

    }

    void UnnamedClientApp::OnDetach()
    {
        
    }
}