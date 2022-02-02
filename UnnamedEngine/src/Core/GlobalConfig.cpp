#include "uepch.h"
#include "Core/GlobalConfig.h"

namespace UE
{
	UEUint32 GlobalConfig::Application::Width = 1280;
	UEUint32 GlobalConfig::Application::Height = 720;
	
	UEFloat GlobalConfig::Rendering::PixelSize = 1.0f;
	UEUint32 GlobalConfig::Rendering::ScreenWidth = GlobalConfig::Application::Width;
	UEUint32 GlobalConfig::Rendering::ScreenHeight = GlobalConfig::Application::Height;
	UEUint32 GlobalConfig::Rendering::DesiredWidth = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenWidth / GlobalConfig::Rendering::PixelSize);
	UEUint32 GlobalConfig::Rendering::DesiredHeight = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenHeight / GlobalConfig::Rendering::PixelSize);

	UEFloat GlobalConfig::Mouse::MovementSensibilityX = 1.0f;
	UEFloat GlobalConfig::Mouse::MovementSensibilityY = 1.0f;
	UEFloat GlobalConfig::Mouse::ScrollSensibilityX = 1.0f;
	UEFloat GlobalConfig::Mouse::ScrollSensibilityY = 1.0f;

	UEFloat GlobalConfig::Zoom::SensibilityIn = 1.0f;
	UEFloat GlobalConfig::Zoom::SensibilityOut = 1.0f;
}