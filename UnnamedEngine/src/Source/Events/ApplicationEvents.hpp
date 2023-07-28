#pragma once

#include "Events/Event.hpp"

namespace UE
{
    class ApplicationStartEvent : public Event
    {
    public:
        ApplicationStartEvent() = default;

        EVENT_CLASS_TYPE(ApplicationStartEvent)
        EVENT_CLASS_CATEGORY(ApplicationEvent)
    };

    class ApplicationStopEvent : public Event
    {
    public:
        ApplicationStopEvent() = default;

        EVENT_CLASS_TYPE(ApplicationStopEvent);
        EVENT_CLASS_CATEGORY(ApplicationEvent);
    };

    class ApplicationHaltEvent : public Event
    {
    public:
        ApplicationHaltEvent() = default;

        EVENT_CLASS_TYPE(ApplicationHaltEvent);
        EVENT_CLASS_CATEGORY(ApplicationEvent);
    };
}