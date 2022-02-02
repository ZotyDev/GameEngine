#include "uepch.h"
#include "ProjectConfig.h"

namespace UE
{
	UEString ProjectConfig::ProjectName = "UnnamedProject";
	UEString ProjectConfig::ProjectLocation = "null";
	UEString ProjectConfig::ProjectVersion = "null";

	UEPath ProjectConfig::AssetPath = "assets";
	UEPath ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;
}