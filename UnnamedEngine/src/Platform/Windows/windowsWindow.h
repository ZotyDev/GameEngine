#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace UE
{
	class WindowsWindow : public Window
	{
	public:
		~WindowsWindow();

		virtual int Init(const WindowProps& props);

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_WindowData.Width; };
		virtual uint32_t GetHeight() const override { return m_WindowData.Height; };
		virtual std::string GetTitle() const override { return m_WindowData.Title; };

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.m_EventCallbackFn = callback; };
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() { return m_Window; };
	private:
		GLFWwindow* m_Window = nullptr;
		Scope<GraphicsContext> m_Context;

		// WindowData class that stores universal attributes
		struct WindowData
		{
			uint32_t Width;
			uint32_t Height;
			std::string Title;
			bool VSync;

			EventCallbackFn m_EventCallbackFn;
		};

		WindowData m_WindowData;
	};
}