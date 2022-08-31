#include "uepch.h"
#include "Project/Project.h"

namespace UE
{
	Project::Header Project::m_ProjectHeader = {};
	UEBool Project::m_IsOpen = false;

	UEResult<> Project::Create(const Project::Header& header)
	{
		return UEResult<>::Success;
	}

	UEResult<> Project::Read(const UEPath& path)
	{
		return UEResult<>::Success;
	}

	UEResult<> Project::Update(const Project::Header& header)
	{
		return UEResult<>::Success;
	}

	UEResult<> Project::Delete(const UEPath& path)
	{
		return UEResult<>::Success;
	}
}