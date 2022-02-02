#pragma once

#include <UnnamedEngine.h>

namespace UE
{
	struct ProjectConfig
	{
		static UEString ProjectName;
		static UEString ProjectLocation;
		static UEString ProjectVersion;

		static UEPath AssetPath;
		static UEPath CurrentDirectory;
	};
}