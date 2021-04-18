#include "WindowsWindow.h"

namespace UE
{
	WindowsWindow::WindowsWindow() {};

	WindowsWindow::~WindowsWindow()
	{
		glfwTerminate();
	};

	int WindowsWindow::Initialize(const char* title, unsigned int width, unsigned int height)
	{
		if (m_Initialized)
		{
			UE_LOG_ERROR("Game Window is already initialized!");
			return -1;
		}

		// Copy properties
		m_WindowData.m_Title = title;
		m_WindowData.m_Width = width;
		m_WindowData.m_Height = height;

		InitGLFW();
		InitWindow(title, width, height);
		
		m_Initialized = true;
		return 0;
	};

	int WindowsWindow::ChangeIcon(const char* iconPath)
	{
		// Load image and check if the image can be loaded
		Image tempImage;
		if (tempImage.Initialize(iconPath, 4))
		{
			UE_LOG_ERROR("Failed to change window icon, image: ", iconPath, " could no be loaded!");
			return -1;
		}

		// NEW operator, possible memory leak!
		GLFWimage* icon = new GLFWimage();
		icon->pixels = tempImage.GetData();
		icon->width = tempImage.GetW();
		icon->height = tempImage.GetH();
		glfwSetWindowIcon(m_Window, 1, icon);

		// Free icon from memory!
		delete icon;

		return 0;
	}

	int WindowsWindow::ChangeIcon(Image sourceImage)
	{
		// NEW operator, possible memory leak!
		GLFWimage* icon = new GLFWimage();
		icon->pixels = sourceImage.GetData();
		icon->width = sourceImage.GetW();
		icon->height = sourceImage.GetH();
		glfwSetWindowIcon(m_Window, 1, icon);

		return 0;
	};

	int WindowsWindow::InitGLFW()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return 0;
	};

	int WindowsWindow::InitVulkan()
	{
		return 0;
	};

	int WindowsWindow::InitWindow(const char* title, unsigned int width, unsigned int height)
	{
		m_Window = glfwCreateWindow(m_WindowData.m_Width, m_WindowData.m_Height, m_WindowData.m_Title, NULL, NULL);
		if (m_Window == NULL)
		{
			UE_LOG_FATAL("Failed to create GLFW Window!");
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			UE_LOG_FATAL("Failed to initialize GLAD!");
			glfwTerminate();
			return -1;
		}

		// SetWindowUserPointer being used to define a pointer to m_WindowData
		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.m_Width = width;
				data.m_Height = height;

				WindowResizeEvent event(width, height);
				data.m_EventCallbackFn(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.m_EventCallbackFn(event);
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
					data.m_EventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.m_EventCallbackFn(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.m_EventCallbackFn(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.m_EventCallbackFn(event);
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
					data.m_EventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.m_EventCallbackFn(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.m_EventCallbackFn(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				// GetWindowUserPointer being used to retrieve a pointer to m_WindowData inside the WindowsWindow class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.m_EventCallbackFn(event);
			});

		// Set Viewport
		glViewport(0, 0, m_WindowData.m_Width, m_WindowData.m_Height);

		return 0;
	};
}