#include "uepch.h"
#include "Core/GlobalConfig.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include <toml.hpp>

namespace UE
{
	UEResult<> GlobalConfig::LoadConfigs()
	{
		// Check if file exist
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load Global Configs: could not find user data folder");
			return UEResult<>::Error;
		}

		// Load config file
		auto ConfigData = toml::parse<toml::preserve_comments>(UserDataFolder.string() + "/UnnamedEngine/GlobalConfig.toml");

		// Create file if it does not exist

		// Create/Compare configs

		// Get configs
		// Window
		auto& WindowConfig = toml::find(ConfigData, "Window");
		Window::Width = toml::find_or<UEUint32>(WindowConfig, "Width", 1280);
		Window::Height = toml::find_or<UEUint32>(WindowConfig, "Height", 720);

		// Renderer
		auto& RendererConfig = toml::find(ConfigData, "Renderer");
		Renderer::PixelSize = toml::find_or<UEFloat>(RendererConfig, "PixelSize", 1.0f);

		// Mouse
		auto& MouseConfig = toml::find(ConfigData, "Mouse");
		Mouse::MovementSensibilityX = toml::find_or<UEFloat>(MouseConfig, "MovementSensibilityX", 1.0f);
		Mouse::MovementSensibilityY = toml::find_or<UEFloat>(MouseConfig, "MovementSensibilityY", 1.0f);
		Mouse::ScrollSensibilityX = toml::find_or<UEFloat>(MouseConfig, "ScrollSensibilityX", 1.0f);
		Mouse::ScrollSensibilityY = toml::find_or<UEFloat>(MouseConfig, "ScrollSensibilityY", 1.0f);

		// Camera
		auto& CameraConfig = toml::find(ConfigData, "Camera");
		Camera::ZoomInSensibility = toml::find_or<UEFloat>(CameraConfig, "ZoomInSensibility", 1.0f);
		Camera::ZoomOutSensibility = toml::find_or<UEFloat>(CameraConfig, "ZoomOutSensibility", 1.0f);


		Renderer::ScreenWidth = Window::Width;
		Renderer::ScreenHeight = Window::Height;
		Renderer::DesiredWidth = (UEUint32)((UEFloat)Renderer::ScreenWidth / Renderer::PixelSize);
		Renderer::DesiredHeight = (UEUint32)((UEFloat)Renderer::ScreenHeight / Renderer::PixelSize);

		return UEResult<>::Success;
	}

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