#pragma once

namespace UE
{
	class Project
	{
	public:
		struct Header 
		{
			UEString Name;
			UEString Version;
			UEPath Location;
		};
	public:
		static UEResult Create(const Project::Header& header);
		static UEResult Read(const UEPath& path);
		static UEResult Update(const Project::Header& header);
		static UEResult Delete(const UEPath& path);

	private:
		static Project::Header m_ProjectHeader;
		static UEBool m_IsOpen;
	};
}