#pragma once

#include "Core/Base.hpp"

namespace UE
{
    class Layer
    {
    public:
        Layer(const UEString& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        const UEString& GetName() const { return m_Name; }
    protected:
        UEString m_Name;
    };
}