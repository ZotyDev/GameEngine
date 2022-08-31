#include "uepch.h"
#include "Window.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "Windows/WindowsWindow.h" 
#endif

namespace UE
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef UE_PLATFORM_WINDOWS
		Scope<Window> t_Window = CreateScope<WindowsWindow>();
		if (!t_Window->Init(props))
		{
			UE_CORE_ERROR("Failed to initialize Window!");
			return nullptr;
		}

		return t_Window;
	#else
		UE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}