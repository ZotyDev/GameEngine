#pragma once

namespace UE
{
	struct PanelsConfig
	{
		static UEBool OptFullscreen;
		static UEBool OptPadding;

		static UEBool MaximizeOnPlay;

		static UEBool ProjectRunning;
		static UEBool ProjectPaused;

		static UEBool ViewportFocused;
		static UEBool ViewportHovered;
	};

	struct PanelsShowConfig
	{
		static UEBool ShowViewport;
		static UEBool ShowContentBrowser;
		static UEBool ShowSceneHierarchy;
		static UEBool ShowProperties;
		static UEBool ShowProfiler;
	};
}