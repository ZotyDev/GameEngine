#include "uepch.h"
#include "Panels/PanelsConfig.h"

#include "Core/ConfigManager.h"

namespace UE
{
	UEResult PanelsConfig::LoadConfigs()
	{
		ConfigManager g;
		UEBool gb;

		g.LoadConfigFile("D:/Documentos/Unnamed Engine/EditorConfig.lua");

		// PanelsConfig
		if (g.GetBoolConfig(gb, { "PanelsConfig", "FullScreen" }) == UEResult::Success)
		{
			PanelsConfig::OptFullscreen = gb;
		}
		if (g.GetBoolConfig(gb, { "PanelsConfig", "Padding" }) == UEResult::Success)
		{
			PanelsConfig::OptPadding = gb;
		}
		if (g.GetBoolConfig(gb, { "PanelsConfig", "MaximizeOnPlay" }) == UEResult::Success)
		{
			PanelsConfig::MaximizeOnPlay = gb;
		}

		// PanelsShowConfig
		if (g.GetBoolConfig(gb, { "ActivePanels", "Viewport" }) == UEResult::Success)
		{
			PanelsShowConfig::ShowViewport = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "ContentBrowser" }) == UEResult::Success)
		{
			PanelsShowConfig::ShowContentBrowser = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "SceneHierarchy" }) == UEResult::Success)
		{
			PanelsShowConfig::ShowSceneHierarchy = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "Properties" }) == UEResult::Success)
		{
			PanelsShowConfig::ShowProperties = gb;
		}
		if (g.GetBoolConfig(gb, { "ActivePanels", "Profiler" }) == UEResult::Success)
		{
			PanelsShowConfig::ShowProfiler = gb;
		}

		return UEResult::Success;
	}

	UEBool PanelsConfig::OptFullscreen = true;
	UEBool PanelsConfig::OptPadding = false;

	UEBool PanelsConfig::MaximizeOnPlay = false;
	
	UEBool PanelsConfig::ProjectRunning = false;
	UEBool PanelsConfig::ProjectPaused = false;

	UEBool PanelsConfig::ViewportFocused = false;
	UEBool PanelsConfig::ViewportHovered = false;

	UEBool PanelsShowConfig::ShowViewport = true;
	UEBool PanelsShowConfig::ShowContentBrowser = true;
	UEBool PanelsShowConfig::ShowProperties = true;
	UEBool PanelsShowConfig::ShowSceneHierarchy = true;
	UEBool PanelsShowConfig::ShowProfiler = false;
}