#pragma once

#include <UnnamedEngine.h>

namespace UE
{
	struct ProjectConfig
	{
		static UEResult LoadConfigs();

		static UEString ProjectName;
		static UEPath ProjectLocation;
		static UEString ProjectVersion;

		static UEPath AssetPath;
		static UEPath CurrentDirectory;
	};
}