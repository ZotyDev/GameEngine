#include "uepch.h"
#include "Core/GlobalConfig.h"

#include "Core/ConfigManager.h"

namespace UE
{
	UEResult GlobalConfig::LoadConfigs()
	{
		ConfigManager g;
		UEDouble gd;
		UEUint32 gu;
		g.LoadConfigFile("D:/Documentos/Unnamed Engine/GlobalConfig.lua");

		// Window
		if (g.GetNumberConfig(gd, { "Window", "Width" }) == UEResult::Success)
		{
			Application::Width = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Window", "Height" }) == UEResult::Success)
		{
			Application::Height = (UEFloat)gd;
		}
		// Renderer
		if (g.GetNumberConfig(gd, { "Renderer", "PixelSize"}) == UEResult::Success)
		{
			Rendering::PixelSize = (UEFloat)gd;
		}
		Rendering::ScreenWidth = Application::Width;
		Rendering::ScreenHeight = Application::Height;
		Rendering::DesiredWidth = (UEUint32)((UEFloat)Rendering::ScreenWidth / Rendering::PixelSize);
		Rendering::DesiredHeight = (UEUint32)((UEFloat)Rendering::ScreenHeight / Rendering::PixelSize);

		// Mouse
		if (g.GetNumberConfig(gd, { "Mouse", "XMovementSensibility" }) == UEResult::Success)
		{
			Mouse::MovementSensibilityX = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "YMovementSensibility" }) == UEResult::Success)
		{
			Mouse::MovementSensibilityY = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "XScrollSensibility" }) == UEResult::Success)
		{
			Mouse::ScrollSensibilityX = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "YScrollSensibility" }) == UEResult::Success)
		{
			Mouse::ScrollSensibilityY = (UEFloat)gd;
		}

		// Camera
		if (g.GetNumberConfig(gd, { "Camera", "ZoomInSensibility" }) == UEResult::Success)
		{
			Zoom::SensibilityIn = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Camera", "ZoomOutSensibility" }) == UEResult::Success)
		{
			Zoom::SensibilityOut = (UEFloat)gd;
		}

		return UEResult::Success;
	}

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