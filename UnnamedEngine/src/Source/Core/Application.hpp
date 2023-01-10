#pragma once

#include "Core/Base.hpp"
#include "Core/LayerStack.hpp"

int main(int argc, char** argv);

namespace UE
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void PushLayer(Ref<Layer> layer);
        void PushOverlay(Ref<Layer> overlay);
        
    public:
        LayerStack m_LayerStack;
        struct SharedData
        {
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

    Application* CreateApplication();
}