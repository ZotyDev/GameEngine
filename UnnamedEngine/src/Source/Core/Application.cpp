#include "uepch.hpp"
#include "Core/Application.hpp"

namespace UE
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Ref<Layer> layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Ref<Layer> overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
    }
}