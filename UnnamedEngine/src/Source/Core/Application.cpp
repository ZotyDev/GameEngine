#include "uepch.hpp"
#include "Core/Application.hpp"

namespace UE
{
    #if defined(UE_PLATFORM_WEB)
    EM_BOOL MainLoopCallback(double time, void* userData)
    {
        auto newData = CreateRef<Application::SharedData>(*(Application::SharedData*)userData);
        Application::s_Instance->MainLoop(newData);
        if(newData->Running)
        {
            return EM_TRUE;
        }
        else
        {
            Application::s_Instance->Stop();
            return EM_FALSE;
        }
    }
    #endif

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
        m_Data->Running = true;

        Run();
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
        m_Data->Running = true;
        
        #if defined(UE_PLATFORM_WINDOWS)
        while(m_Data->Running)
        {
            MainLoop(m_Data);
        }
        Stop();
        #elif defined(UE_PLATFORM_WEB)
        {
            emscripten_request_animation_frame_loop(MainLoopCallback, (void*)m_Data.get());
        }
        #endif
    }

    UEUint64 count = 0;

    void Application::MainLoop(Ref<SharedData> data)
    {
        count++;
        if (!(count % 60))
        {
            UE_LOG_CORE_TRACE("Running? {} {}", data->Running, count);
        }
    }

    void Application::Stop()
    {
        delete this;
        UE_LOG_CORE_INFO("Everything went ok! See you again soon :D");
    }
    
}