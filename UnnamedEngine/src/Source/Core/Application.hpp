#pragma once

#include "Core/Base.hpp"
#include "Core/LayerStack.hpp"

#if defined (UE_PLATFORM_WINDOWS) || \
    defined (UE_PLATFORM_LINUX)   || \
    defined (UE_PLATFORM_EMSCRIPTEN)
    int main(int argc, char** argv);
#endif

namespace UE
{
    class Application
    {
    public:
        Application(const EntryArgs& args);
        virtual ~Application();

        void PushLayer(Ref<Layer> layer);
        void PushOverlay(Ref<Layer> overlay);
        
    public:
        LayerStack m_LayerStack;
        // Data that is constantly used across the engine
        struct SharedData
        {
            EntryArgs Args;
            UEBool Running = true;
        };

        Ref<SharedData> m_Data = CreateRef<SharedData>();
    public:
        void Run();
        void MainLoop(Ref<SharedData> data);
        void Stop();
    public:
        static Application* s_Instance;
    private:
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(const EntryArgs& args);
}