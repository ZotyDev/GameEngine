#pragma once

#include "Project/Project.h"

namespace UE
{
	class ProjectSerializer
	{
	public:

		static UEResult<> Serialize(const UEPath& path);
		static UEResult<> Deserialize(const UEPath& path);
	};
}