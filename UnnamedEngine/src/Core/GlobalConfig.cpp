#include "uepch.h"
#include "Core/GlobalConfig.h"

#include "Core/ConfigManager.h"

#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	UEResult<> GlobalConfig::LoadConfigs()
	{
		ConfigManager g;
		UEDouble gd;
		UEUint32 gu;
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load Global Configs: could not find user data folder");
			return UEResult<>::Error;
		}
		g.LoadConfigFile(UserDataFolder.string() + "/UnnamedEngine/GlobalConfig.lua", "assets/configs/default/DEFAULT_GlobalConfig.lua");

		// Window
		if (g.GetNumberConfig(gd, { "Window", "Width" }))
		{
			Application::Width = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Window", "Height" }))
		{
			Application::Height = (UEFloat)gd;
		}
		// Renderer
		if (g.GetNumberConfig(gd, { "Renderer", "PixelSize"}))
		{
			Rendering::PixelSize = (UEFloat)gd;
		}
		Rendering::ScreenWidth = Application::Width;
		Rendering::ScreenHeight = Application::Height;
		Rendering::DesiredWidth = (UEUint32)((UEFloat)Rendering::ScreenWidth / Rendering::PixelSize);
		Rendering::DesiredHeight = (UEUint32)((UEFloat)Rendering::ScreenHeight / Rendering::PixelSize);

		// Mouse
		if (g.GetNumberConfig(gd, { "Mouse", "XMovementSensibility" }))
		{
			Mouse::MovementSensibilityX = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "YMovementSensibility" }))
		{
			Mouse::MovementSensibilityY = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "XScrollSensibility" }))
		{
			Mouse::ScrollSensibilityX = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Mouse", "YScrollSensibility" }))
		{
			Mouse::ScrollSensibilityY = (UEFloat)gd;
		}

		// Camera
		if (g.GetNumberConfig(gd, { "Camera", "ZoomInSensibility" }))
		{
			Zoom::SensibilityIn = (UEFloat)gd;
		}
		if (g.GetNumberConfig(gd, { "Camera", "ZoomOutSensibility" }))
		{
			Zoom::SensibilityOut = (UEFloat)gd;
		}

		return UEResult<>::Success;
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