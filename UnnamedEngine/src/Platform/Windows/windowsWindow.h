#pragma once

#include "Core.h"
#include "Window/Window.h"

#include "Logger/Logger.h"
#include "Time/LocalTime.h"

/*
	WindowResizeCallBack need to be converted to a 'event friendly' alternative
*/

namespace UE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();
		~WindowsWindow();

		int Initialize(const char* title, unsigned int width, unsigned int height);
		void* GetNativeWindow() { return m_Window; };

		int ChangeIcon(const char* iconPath);
		int ChangeIcon(Image sourceImage);
		void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.m_EventCallbackFn = callback; };

		unsigned int GetWidth() const override { return m_WindowData.m_Width; };
		unsigned int GetHeight() const override { return m_WindowData.m_Height; };
		const char* GetTitle() const override { return m_WindowData.m_Title; };

		int InitGLFW();
		int InitVulkan();

		int InitWindow(const char* title, unsigned int width, unsigned int height);

	private:
		GLFWwindow* m_Window = nullptr;

		// WindowData class that stores universal attributes
		struct WindowData
		{
			unsigned int m_Width = 0;
			unsigned int m_Height = 0;
			const char* m_Title = 0;

			EventCallbackFn m_EventCallbackFn;
		};

		WindowData m_WindowData;
	};
}