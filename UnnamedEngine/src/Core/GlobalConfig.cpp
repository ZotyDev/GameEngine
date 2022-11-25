#include "uepch.h"
#include "Core/GlobalConfig.h"

namespace UE
{
	UEUint32 GlobalConfig::Window::Width = 1280;
	UEUint32 GlobalConfig::Window::Height = 720;
	
	UEFloat GlobalConfig::Renderer::PixelSize = 1.0f;
	UEUint32 GlobalConfig::Renderer::ScreenWidth = GlobalConfig::Window::Width;
	UEUint32 GlobalConfig::Renderer::ScreenHeight = GlobalConfig::Window::Height;
	UEUint32 GlobalConfig::Renderer::DesiredWidth = (UEUint32)((UEFloat)GlobalConfig::Renderer::ScreenWidth / GlobalConfig::Renderer::PixelSize);
	UEUint32 GlobalConfig::Renderer::DesiredHeight = (UEUint32)((UEFloat)GlobalConfig::Renderer::ScreenHeight / GlobalConfig::Renderer::PixelSize);

	UEFloat GlobalConfig::Mouse::MovementSensibilityX = 1.0f;
	UEFloat GlobalConfig::Mouse::MovementSensibilityY = 1.0f;
	UEFloat GlobalConfig::Mouse::ScrollSensibilityX = 1.0f;
	UEFloat GlobalConfig::Mouse::ScrollSensibilityY = 1.0f;

	UEFloat GlobalConfig::Camera::ZoomInSensibility = 1.0f;
	UEFloat GlobalConfig::Camera::ZoomOutSensibility = 1.0f;
}