#pragma once

#include "Pch.h"

namespace UE
{

	/*
		Check if a file exist in the specified path
	*/
	bool FileExists(const char* path);

	/*
		Check if is big endian
	*/
	inline bool IsBigEndian() 
	{
		union
		{
			long int l;
			char c[sizeof(long int)];
		} u;

		u.l = 1;

		if (u.c[sizeof(long int)-1] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	/*
	*	Convert char buffer to int
	*/
	std::int32_t _convert_to_int(char* buffer, std::size_t len);
}