#pragma once

#include "Core/Base.hpp"

#include "Events/Event.hpp"

namespace UE
{
    class Layer
    {
    public:
        Layer(const UEString& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}

        virtual void OnEvent(Event& event) {}

        const UEString& GetName() const { return m_Name; }
    protected:
        UEString m_Name;
    };
}
