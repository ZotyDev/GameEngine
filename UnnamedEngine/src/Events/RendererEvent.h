#pragma once

#include "Events/event.h"

namespace UE
{
	class RendererEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryRenderer)
	};

	class RendererScaleChangeEvent : public RendererEvent
	{
	public:
		EVENT_CLASS_TYPE(RendererScaleChange)
	};
}