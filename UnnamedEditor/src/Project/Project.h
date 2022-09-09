#pragma once

namespace UE
{
	class Project
	{
	public:
		struct Header 
		{
			static UEString Name;
			static UEString Version;
			static UEPath Location;

			static UEPath AssetPath;
			static UEPath CurrentDirectory;

			static UEBool IsOpen;
		};
	public:
		static UEResult<> Create(const Project::Header& header);
		static UEResult<> Read(const UEPath& path);
		static UEResult<> ReadLatest();
	};
}