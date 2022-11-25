#pragma once

namespace UE
{
	class ProjectSerializer
	{
	public:

		static UEResult<> Serialize(const UEPath& path);
		static UEResult<> Deserialize(const UEPath& path);
	};
}