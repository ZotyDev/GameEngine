#pragma once

#include <UnnamedEngine.hpp>

namespace UE
{
    class UnnamedClientApp : public Layer
    {
    public:
        UnnamedClientApp(Ref<Application::SharedData> data);
        virtual ~UnnamedClientApp() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
    private:
        Ref<Application::SharedData> m_Data;
    };
}