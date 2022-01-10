#include "uepch.h"
#include "Panels/PanelsConfig.h"

namespace UE
{
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