#pragma once

#include "Core/Base.h"
#include "Events/Event.h"

#include "Core/GlobalConfig.h"

namespace UE
{
	struct WindowProps
	{
		UEString Title;
		UEUint32 Width;
		UEUint32 Height;

		WindowProps(const UEString& title = "UnnamedEngine",
			UEUint32 width = GlobalConfig::Application::Width,
			UEUint32 height = GlobalConfig::Application::Height)
			: Title(title), Width(width), Height(height)
		{}
	};

	// Base Window class for DESKTOP ONLY version
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;
		virtual UEResult<> Init(const WindowProps& props) = 0;

		virtual void OnUpdate() = 0;

		virtual UEString GetTitle() const = 0;
		virtual UEUint32 GetWidth() const = 0;
		virtual UEUint32 GetHeight() const = 0;

		virtual void SetWindowEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetInputEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetFullscreen(bool enabled) = 0;
		virtual void SetHidden(bool enabled) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual UEResult<> SetIcon(const UEString& path) = 0;

		virtual void SetCursorHidden(bool hidden) = 0;

		virtual void* GetNativeWindow() = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
