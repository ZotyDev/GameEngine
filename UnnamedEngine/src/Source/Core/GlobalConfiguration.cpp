#include "Core/GlobalConfiguration.hpp"

namespace UE
{
	UEUint32 GlobalConfiguration::Window::Width  = 1280;
	UEUint32 GlobalConfiguration::Window::Height = 720;

	UEFloat  GlobalConfiguration::Renderer::PixelSize     = 1.0f;
	UEUint32 GlobalConfiguration::Renderer::ScreenWidth   = GlobalConfiguration::Window::Width;
	UEUint32 GlobalConfiguration::Renderer::ScreenHeight  = GlobalConfiguration::Window::Height;
	UEUint32 GlobalConfiguration::Renderer::DesiredWidth  = (UEUint32)((UEFloat)GlobalConfiguration::Renderer::ScreenWidth / GlobalConfiguration::Renderer::PixelSize);
	UEUint32 GlobalConfiguration::Renderer::DesiredHeight = (UEUint32)((UEFloat)GlobalConfiguration::Renderer::ScreenHeight / GlobalConfiguration::Renderer::PixelSize);

	UEFloat GlobalConfiguration::Mouse::MovementSensibilityX = 1.0f;
	UEFloat GlobalConfiguration::Mouse::MovementSensibilityY = 1.0f;
	UEFloat GlobalConfiguration::Mouse::ScrollSensibilityX   = 1.0f;
	UEFloat GlobalConfiguration::Mouse::ScrollSensibilityY   = 1.0f;

	UEFloat GlobalConfiguration::Camera::ZoomInSensibility  = 1.0f;
	UEFloat GlobalConfiguration::Camera::ZoomOutSensibility = 1.0f;
}
