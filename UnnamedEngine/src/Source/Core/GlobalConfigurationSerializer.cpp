#include "Core/GlobalConfigurationSerializer.hpp"

#include "Core/GlobalConfiguration.hpp"
#include "Core/PlatformIndependenceLayer/Filesystem.hpp"

#include <yaml-cpp/yaml.h>

namespace UE
{
    UEResult<> GlobalConfigurationSerializer::Serialize()
    {
        //////////////////////////////////////////////////
        // Start
        YAML::Emitter Out;
        Out << YAML::BeginMap;

        // Window
        Out << YAML::Key << "Window" << YAML::BeginMap;
		Out << YAML::Key << "Width"  << YAML::Value << GlobalConfiguration::Window::Width;
		Out << YAML::Key << "Height" << YAML::Value << GlobalConfiguration::Window::Height;
		Out << YAML::EndMap;

        // Renderer
		Out << YAML::Key << "Renderer"  << YAML::BeginMap;
		Out << YAML::Key << "PixelSize" << YAML::Value << GlobalConfiguration::Renderer::PixelSize;
		Out << YAML::EndMap;

        // Mouse
		Out << YAML::Key << "Mouse"                << YAML::BeginMap;
		Out << YAML::Key << "MovementSensibilityX" << YAML::Value << GlobalConfiguration::Mouse::MovementSensibilityX;
		Out << YAML::Key << "MovementSensibilityY" << YAML::Value << GlobalConfiguration::Mouse::MovementSensibilityY;
		Out << YAML::Key << "ScrollSensibilityX"   << YAML::Value << GlobalConfiguration::Mouse::ScrollSensibilityX;
		Out << YAML::Key << "ScrollSensibilityY"   << YAML::Value << GlobalConfiguration::Mouse::ScrollSensibilityY;
		Out << YAML::EndMap;

        // Camera
		Out << YAML::Key << "Camera"             << YAML::BeginMap;
		Out << YAML::Key << "ZoomInSensibility"  << YAML::Value << GlobalConfiguration::Camera::ZoomInSensibility;
		Out << YAML::Key << "ZoomOutSensibility" << YAML::Value << GlobalConfiguration::Camera::ZoomOutSensibility;
		Out << YAML::EndMap;

        //////////////////////////////////////////////////
        // End
        Out << YAML::EndMap;

        //////////////////////////////////////////////////
        // Write data to GlobalConfiguration.yaml
        Filesystem::Write("UnnamedEngine/GlobalConfiguration.yaml", Out.c_str(), Filesystem::WriteMode::Overwrite, Filesystem::Path::UserData);

        return UEResult<>::Success;
    }

    UEResult<> GlobalConfigurationSerializer::Deserialize()
    {
		//////////////////////////////////////////////////
        // Make sure that GlobalConfiguration.yaml atleast exists
		UEBool Exists = Filesystem::MakeSure("UnnamedEngine/GlobalConfiguration.yaml", Filesystem::Path::UserData).Value;

        //////////////////////////////////////////////////
        // Load the data from GlobalConfiguration.yaml
        YAML::Node Data;
        try
		{
			Data = YAML::LoadFile(Filesystem::GetUserDataPath().string() + "/UnnamedEngine/GlobalConfiguration.yaml");
		}
		catch (YAML::ParserException e)
		{
			UE_LOG_CORE_ERROR("Failed to load global configs: {}", e.what());
			return UEResult<>::Error;
		}

        auto Window   = Data["Window"];
        auto Renderer = Data["Renderer"];
        auto Mouse    = Data["Mouse"];
        auto Camera   = Data["Camera"];

        // Window  		
        GlobalConfiguration::Window::Width  = Window["Width"].as<UEUint32>(GlobalConfiguration::Window::Width);
		GlobalConfiguration::Window::Height = Window["Height"].as<UEUint32>(GlobalConfiguration::Window::Height);

        // Renderer
		GlobalConfiguration::Renderer::PixelSize     = Renderer["PixelSize"].as<UEFloat>(GlobalConfiguration::Renderer::PixelSize);
		GlobalConfiguration::Renderer::ScreenWidth   = GlobalConfiguration::Window::Width;
		GlobalConfiguration::Renderer::ScreenHeight  = GlobalConfiguration::Window::Height;
		GlobalConfiguration::Renderer::DesiredWidth  = (UEUint32)((UEFloat)GlobalConfiguration::Renderer::ScreenWidth / GlobalConfiguration::Renderer::PixelSize);
		GlobalConfiguration::Renderer::DesiredHeight = (UEUint32)((UEFloat)GlobalConfiguration::Renderer::ScreenHeight / GlobalConfiguration::Renderer::PixelSize);

		// Mouse
		GlobalConfiguration::Mouse::MovementSensibilityX = Mouse["MovementSensibilityX"].as<UEFloat>(GlobalConfiguration::Mouse::MovementSensibilityX);
		GlobalConfiguration::Mouse::MovementSensibilityY = Mouse["MovementSensibilityY"].as<UEFloat>(GlobalConfiguration::Mouse::MovementSensibilityY);
		GlobalConfiguration::Mouse::ScrollSensibilityX   = Mouse["ScrollSensibilityX"].as<UEFloat>(GlobalConfiguration::Mouse::ScrollSensibilityX);
		GlobalConfiguration::Mouse::ScrollSensibilityY   = Mouse["ScrollSensibilityY"].as<UEFloat>(GlobalConfiguration::Mouse::ScrollSensibilityY);

		// Camera
		GlobalConfiguration::Camera::ZoomInSensibility  = Camera["ZoomInSensibility"].as<UEFloat>(GlobalConfiguration::Camera::ZoomInSensibility);
		GlobalConfiguration::Camera::ZoomOutSensibility = Camera["ZoomOutSensibility"].as<UEFloat>(GlobalConfiguration::Camera::ZoomOutSensibility);

		if (!Exists)
		{
			GlobalConfigurationSerializer::Serialize();
		}

        return UEResult<>::Success;
    }
}