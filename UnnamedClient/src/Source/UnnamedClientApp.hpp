#pragma once

#include <UnnamedEngine.hpp>

namespace UE
{
    class UnnamedClientApp : public Layer
    {
    public:
        UnnamedClientApp();
        virtual ~UnnamedClientApp() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;

        virtual void OnEvent(Event& event) override;
    private:
		Ref<Application::SharedData> m_Data;
    };
}
