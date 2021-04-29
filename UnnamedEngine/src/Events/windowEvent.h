#pragma once

#include "Events/Event.h"

namespace UE
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) 
			: m_Width(width), m_Height(height) 
		{}

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

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;
		
		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(unsigned int windowX, unsigned int windowY)
			: m_WindowX(windowX), m_WindowY(windowY)
		{}

		unsigned int GetWindowX() const { return m_WindowX; }
		unsigned int GetWindowY() const { return m_WindowY; }

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	private:
		unsigned int m_WindowX;
		unsigned int m_WindowY;
	};
}