#include "Core/Application.hpp"

#include "Core/PlatformIndependenceLayer/Filesystem.hpp"
#include "Core/GlobalConfigurationSerializer.hpp"

namespace UE
{
    // Function that will be used by Emscripten, since we can't use while(true)
    // loops in the browser we need to make the main loop in a different way.
    #if defined(UE_PLATFORM_EMSCRIPTEN)
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

    // Constructor
    Application::Application(const EntryArgs& args)
    {
        s_Instance = this;
        m_Data->Running = true;
        m_Data->Args = args;

        Filesystem::SetUserDataPath();

        // Load the global configuration
        GlobalConfigurationSerializer::Deserialize();

        Run();
    }

    // Destructor
    Application::~Application()
    {
        Stop();
    }

    // Pushes a layer
    void Application::PushLayer(Ref<Layer> layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    // Pushes a layer as a overlay
    void Application::PushOverlay(Ref<Layer> overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    // Runs the engine
    void Application::Run()
    {
        m_Data->Running = true;
        
        // Desktop platform
        #if defined(UE_PLATFORM_WINDOWS) || \
            defined(UE_PLATFORM_LINUX)   || \
            defined(UE_PLATFORM_MACOS)
        while(m_Data->Running)
        {
            MainLoop(m_Data);
        }
        Stop();
        
        // Emscripten (does not allow while(true) loop)
        #elif defined(UE_PLATFORM_EMSCRIPTEN)
        {
            emscripten_request_animation_frame_loop(MainLoopCallback, (void*)m_Data.get());
        }
        #endif
    }

    // The main loop
    void Application::MainLoop(Ref<SharedData> data)
    {

    }

    // Called when the engine stops
    void Application::Stop()
    {
        // Save the global configuration
        GlobalConfigurationSerializer::Serialize();

        UE_LOG_CORE_INFO("Everything went ok! See you again soon :D");
    }
    
}