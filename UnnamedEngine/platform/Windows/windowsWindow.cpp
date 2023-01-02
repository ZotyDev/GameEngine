#include "uepch.h"
#include "WindowsWindow.h"

#include <stb_image.h>

#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include "Renderer/Renderer.h"

#include "Renderer/GraphicsContext.h"

#include "Core/GlobalConfig.h"

namespace UE
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		UE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	};

	UEResult<> WindowsWindow::Init(const WindowProps& props)
	{
		// Copy properties
		m_WindowData.Title = props.Title;
		m_WindowData.Width = props.Width;
		m_WindowData.Height = props.Height;

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			UE_CORE_ASSERT(success, "Failed to initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			switch (RendererAPI::GetAPI())
			{
			case RendererAPI::API::None:
				UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				break;
			#if defined(UE_PLATFORM_OPENGL)
			case RendererAPI::API::OpenGL:
				glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
				
				#if defined(UE_DEBUG)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
				#endif

				break;
			#endif
			#if defined(UE_PLATFORM_VULKAN)
			case RendererAPI::API::Vulkan:
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
				break;
			#endif
			}

			glfwWindowHint(GLFW_SAMPLES, 4);

			m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
			int PosX = 0;
			int PosY = 0;
			glfwGetWindowPos(m_Window, &PosX, &PosY);
			m_WindowData.PosX = PosX;
			m_WindowData.PosY = PosY;
			++s_GLFWWindowCount;

		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		// SetWindowUserPointer being used to define a pointer to m_WindowData
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		//SetVSync(true);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.m_WindowEventCallbackFn(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.m_WindowEventCallbackFn(event);
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);				
				if (focused)
				{
					WindowFocusEvent event;
					data.m_WindowEventCallbackFn(event);
				}
				else
				{
					WindowLostFocusEvent event;
					data.m_WindowEventCallbackFn(event);
				}
			});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.PosX = xpos;
				data.PosY = ypos;
				WindowMovedEvent event(xpos, ypos);
				data.m_WindowEventCallbackFn(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.m_InputEventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.m_InputEventCallbackFn(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.m_InputEventCallbackFn(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.m_InputEventCallbackFn(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.m_InputEventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.m_InputEventCallbackFn(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.m_InputEventCallbackFn(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.m_InputEventCallbackFn(event);
			});

		// Set Viewport
		RenderCommand::SetViewport(0, 0, GlobalConfig::Renderer::ScreenWidth, GlobalConfig::Renderer::ScreenHeight);

		return UEResult<>::Success;
	};

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetFullscreen(bool enabled)
	{
		GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* PrimaryMonitorVidMode = glfwGetVideoMode(PrimaryMonitor);

		if (enabled)
		{
			m_WindowData.WindowedWidth = m_WindowData.Width;
			m_WindowData.WindowedHeight = m_WindowData.Height;
			m_WindowData.WindowedPosX = m_WindowData.PosX;
			m_WindowData.WindowedPosY = m_WindowData.PosY;
			glfwSetWindowMonitor(m_Window, PrimaryMonitor, 0, 0, PrimaryMonitorVidMode->width, PrimaryMonitorVidMode->height, PrimaryMonitorVidMode->refreshRate);
		}
		else
		{
			m_WindowData.Width = m_WindowData.WindowedWidth;
			m_WindowData.Height = m_WindowData.WindowedHeight;
			m_WindowData.PosX = m_WindowData.WindowedPosX;
			m_WindowData.PosY = m_WindowData.WindowedPosY;
			glfwSetWindowMonitor(m_Window, NULL, m_WindowData.PosX, m_WindowData.PosY, m_WindowData.Width, m_WindowData.Height, GLFW_DONT_CARE);
		}
	}

	void WindowsWindow::SetHidden(bool enabled)
	{
		if (enabled)
		{
			glfwHideWindow(m_Window);
		}
		else
		{
			glfwShowWindow(m_Window);
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_WindowData.VSync = enabled;
	}

	void WindowsWindow::SetTitle(UEString title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_WindowData.VSync;
	}

	UEResult<> WindowsWindow::SetIcon(const UEString& path)
	{
		GLFWimage IconImage;
		IconImage.pixels = nullptr;

		stbi_set_flip_vertically_on_load(0);
		IconImage.pixels = stbi_load(path.c_str(), &IconImage.width, &IconImage.height, nullptr, 0);
		if (!IconImage.pixels)
		{
			UE_CORE_ERROR("Failed to set icon of WindowsWindow: {0} not found", path);
			return UEResult<>::Error;
		}

		glfwSetWindowIcon(m_Window, 1, &IconImage);

		stbi_image_free(IconImage.pixels);

		return UEResult<>::Success;
	}

	void WindowsWindow::SetCursorHidden(bool hidden)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, hidden ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}
}