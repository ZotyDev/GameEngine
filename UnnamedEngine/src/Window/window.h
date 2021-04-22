#pragma once

#include "Core.h"

#include "Image/Image.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

namespace UE
{
	// Base Window class for DESKTOP ONLY version
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;
		virtual int Initialize(const char* title, unsigned int width, unsigned int height) = 0;
		virtual int ChangeIcon(const char* iconPath) = 0;
		virtual int ChangeIcon(Image sourceImage) = 0;
		virtual void* GetNativeWindow() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual const char* GetTitle() const = 0;

	protected:
		bool m_Initialized = false;
	};
}
