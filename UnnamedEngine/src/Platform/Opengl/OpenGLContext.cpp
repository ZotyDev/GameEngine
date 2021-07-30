#include "uepch.h"
#include "Platform/Opengl/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace UE
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		UE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(status, "Failed to initialize GLFW!");

		UE_CORE_INFO("OpenGL Info:\n Vendor: {0}\n Renderer: {1}\n Version: {2}",
			glGetString(GL_VENDOR),
			glGetString(GL_RENDERER),
			glGetString(GL_VERSION));

		UE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 6), "UnnamedEngine requires at least OpenGL version 4.6");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}