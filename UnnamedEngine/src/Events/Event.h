#pragma once

#include "Core/Base.h"

namespace UE
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		GamepadButtonPressed, GamepadButtonReleased, GamepadAxisUpdated,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		ClientConnected, ClientDisconnected, ClientPacket,
		ServerConnected, ServerDisconnected, ServerPacket,
		RendererScaleChange,
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow			= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
		EventCategoryGamepad		= BIT(5),
		EventCategoryNetwork		= BIT(6),
		EventCategoryRenderer		= BIT(7),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
																virtual EventType GetEventType() const override {return GetStaticType(); }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		};
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) 
		{
		};

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}