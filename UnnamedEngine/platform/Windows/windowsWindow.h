#pragma once

#include "Core/Window.h"

#include <GLFW/glfw3.h>

#include "Renderer/GraphicsContext.h"

namespace UE
{
	class WindowsWindow : public Window
	{
	public:
		~WindowsWindow();

		virtual UEResult<> Init(const WindowProps& props) override;

		virtual void OnUpdate() override;

		virtual UEUint32 GetWidth() const override { return m_WindowData.Width; }
		virtual UEUint32 GetHeight() const override { return m_WindowData.Height; }
		virtual UEString GetTitle() const override { return m_WindowData.Title; }

		virtual void SetWindowEventCallback(const EventCallbackFn& callback) override { m_WindowData.m_WindowEventCallbackFn = callback; }
		virtual void SetInputEventCallback(const EventCallbackFn& callback) override { m_WindowData.m_InputEventCallbackFn = callback; }
		virtual void SetHidden(bool enabled) override;
		virtual void SetFullscreen(bool enabled) override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual UEResult<> SetIcon(const UEString& path) override;

		virtual void SetCursorHidden(bool hidden) override;

		virtual void* GetNativeWindow() override { return m_Window; }
	private:
		GLFWwindow* m_Window = nullptr;
		Scope<GraphicsContext> m_Context;

		// WindowData class that stores universal attributes
		struct WindowData
		{
			UEUint32 Width;
			UEUint32 Height;
			UEUint32 PosX;
			UEUint32 PosY;
			UEUint32 WindowedWidth;
			UEUint32 WindowedHeight;
			UEUint32 WindowedPosX;
			UEUint32 WindowedPosY;
			UEString Title;
			bool VSync;

			EventCallbackFn m_WindowEventCallbackFn;
			EventCallbackFn m_InputEventCallbackFn;
		};

		WindowData m_WindowData;
	};
}