#include "uepch.h"
#include "EditorConfig.h"

namespace UE
{
	UEBool ProjectConfig::ProjectRunning = false;
	UEBool ProjectConfig::ProjectPaused = false;
	std::vector<UEString> ProjectConfig::RecentProjects = std::vector<UEString>();
	
	UEBool PanelsConfig::Fullscreen = true;
	UEBool PanelsConfig::Padding = false;
	UEBool PanelsConfig::MaximizeOnPlay = false;
	UEBool PanelsConfig::ViewportFocused = false;
	UEBool PanelsConfig::ViewportHovered = false;
	
	UEBool ActivePanelsConfig::Viewport = true;
	UEBool ActivePanelsConfig::ContentBrowser = true;
	UEBool ActivePanelsConfig::SceneHierarchy = true;
	UEBool ActivePanelsConfig::Properties = true;
	UEBool ActivePanelsConfig::Profiler = false;
	UEBool ActivePanelsConfig::NodeEditor = false;
	
}