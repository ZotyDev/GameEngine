#pragma once

#include "Events/Event.h"

namespace UE
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) 
		{
		};

		unsigned int GetWidth() const { return m_Width; };
		unsigned int GetHeight() const { return m_Height; };

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};
}