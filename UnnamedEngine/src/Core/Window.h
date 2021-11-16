#pragma once

#include "Core/Base.h"
#include "Events/Event.h"

namespace UE
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "UnnamedEngine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Base Window class for DESKTOP ONLY version
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;
		virtual int Init(const WindowProps& props) = 0;

		virtual void OnUpdate() = 0;

		virtual std::string GetTitle() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetWindowEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetInputEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual UEResult SetIcon(const std::string& path) = 0;

		virtual void SetCursorHidden(bool hidden) = 0;

		virtual void* GetNativeWindow() = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
