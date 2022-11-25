#include "uepch.h"
#include "GlobalConfigSerializer.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include "Core/GlobalConfig.h"

namespace UE
{
	UEResult<> GlobalConfigSerializer::Serialize()
	{
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to save global configs: could not find user data folder");
			return UEResult<>::Error;
		}

		YAML::Emitter out;
		out << YAML::BeginMap;

		out << YAML::Key << "Window" << YAML::BeginMap;
		out << YAML::Key << "Width" << YAML::Value << GlobalConfig::Window::Width;
		out << YAML::Key << "Height" << YAML::Value << GlobalConfig::Window::Height;
		out << YAML::EndMap; // Window

		out << YAML::Key << "Renderer" << YAML::BeginMap;
		out << YAML::Key << "PixelSize" << YAML::Value << GlobalConfig::Renderer::PixelSize;
		out << YAML::EndMap; // Renderer

		out << YAML::Key << "Mouse" << YAML::BeginMap;
		out << YAML::Key << "MovementSensibilityX" << YAML::Value << GlobalConfig::Mouse::MovementSensibilityX;
		out << YAML::Key << "MovementSensibilityY" << YAML::Value << GlobalConfig::Mouse::MovementSensibilityY;
		out << YAML::Key << "ScrollSensibilityX" << YAML::Value << GlobalConfig::Mouse::ScrollSensibilityX;
		out << YAML::Key << "ScrollSensibilityY" << YAML::Value << GlobalConfig::Mouse::ScrollSensibilityY;
		out << YAML::EndMap; // Mouse

		out << YAML::Key << "Camera" << YAML::BeginMap;
		out << YAML::Key << "ZoomInSensibility" << YAML::Value << GlobalConfig::Camera::ZoomInSensibility;
		out << YAML::Key << "ZoomOutSensibility" << YAML::Value << GlobalConfig::Camera::ZoomOutSensibility;
		out << YAML::EndMap; // Camera

		out << YAML::EndMap;

		std::ofstream FileOutput(UserDataFolder.string() + "/UnnamedEngine/GlobalConfig.yaml");
		FileOutput << out.c_str();

		return UEResult<>::Success;
	}

	UEResult<> GlobalConfigSerializer::Deserialize()
	{
		UEPath UserDataFolder;
		if (!FileSystem::GetUserDataFolder(UserDataFolder))
		{
			UE_CORE_ERROR("Failed to load global configs: could not find user data folder");
			return UEResult<>::Error;
		}

		YAML::Node Data;
		try
		{
			Data = YAML::LoadFile(UserDataFolder.string() + "/UnnamedEngine/GlobalConfig.yaml");
		}
		catch (YAML::ParserException e)
		{
			UE_CORE_ERROR("Failed to load global configs: {0}", e.what());
			return UEResult<>::Error;
		}

		auto Window = Data["Window"];
		auto Renderer = Data["Renderer"];
		auto Mouse = Data["Mouse"];
		auto Camera = Data["Camera"];

		// Window
		GlobalConfig::Window::Width = Window["Width"].as<UEUint32>(GlobalConfig::Window::Width);
		GlobalConfig::Window::Height = Window["Height"].as<UEUint32>(GlobalConfig::Window::Height);

		// Renderer
		GlobalConfig::Renderer::PixelSize = Renderer["PixelSize"].as<UEFloat>(GlobalConfig::Renderer::PixelSize);
		GlobalConfig::Renderer::ScreenWidth = GlobalConfig::Window::Width;
		GlobalConfig::Renderer::ScreenHeight = GlobalConfig::Window::Height;
		GlobalConfig::Renderer::DesiredWidth = (UEUint32)((UEFloat)GlobalConfig::Renderer::ScreenWidth / GlobalConfig::Renderer::PixelSize);
		GlobalConfig::Renderer::DesiredHeight = (UEUint32)((UEFloat)GlobalConfig::Renderer::ScreenHeight / GlobalConfig::Renderer::PixelSize);

		// Mouse
		GlobalConfig::Mouse::MovementSensibilityX = Mouse["MovementSensibilityX"].as<UEFloat>(GlobalConfig::Mouse::MovementSensibilityX);
		GlobalConfig::Mouse::MovementSensibilityY = Mouse["MovementSensibilityY"].as<UEFloat>(GlobalConfig::Mouse::MovementSensibilityY);
		GlobalConfig::Mouse::ScrollSensibilityX = Mouse["ScrollSensibilityX"].as<UEFloat>(GlobalConfig::Mouse::ScrollSensibilityX);
		GlobalConfig::Mouse::ScrollSensibilityY = Mouse["ScrollSensibilityY"].as<UEFloat>(GlobalConfig::Mouse::ScrollSensibilityY);

		// Camera
		GlobalConfig::Camera::ZoomInSensibility = Camera["ZoomInSensibility"].as<UEFloat>(GlobalConfig::Camera::ZoomInSensibility);
		GlobalConfig::Camera::ZoomOutSensibility = Camera["ZoomOutSensibility"].as<UEFloat>(GlobalConfig::Camera::ZoomOutSensibility);

		return UEResult<>::Success;
	}
}