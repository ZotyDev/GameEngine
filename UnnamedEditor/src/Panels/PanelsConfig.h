#pragma once

namespace UE
{
	struct PanelsConfig
	{
		static UEResult<> LoadConfigs();

		static UEBool Fullscreen;
		static UEBool Padding;

		static UEBool MaximizeOnPlay;

		static UEBool ProjectRunning;
		static UEBool ProjectPaused;

		static UEBool ViewportFocused;
		static UEBool ViewportHovered;
	};

	struct ActivePanelsConfig
	{
		static UEBool Viewport;
		static UEBool ContentBrowser;
		static UEBool SceneHierarchy;
		static UEBool Properties;
		static UEBool Profiler;
		static UEBool NodeEditor;
	};
}