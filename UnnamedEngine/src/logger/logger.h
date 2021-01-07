#pragma once

#include "pch.h"

void PrintTest()
{
	std::cout << "TEST" << std::endl;
}

namespace Logger
{
	__declspec(dllexport) std::list<std::string> LogList;
	std::ofstream FileOut;

	template<typename Arg>
	void _construct_string_from_args(std::ostringstream& out, Arg arg)
	{
		out << arg;
	}

	template<typename Arg, typename... Args>
	void _construct_string_from_args(std::ostringstream& out, Arg arg, Args... args)
	{
		out << arg;
		_construct_string_from_args(out, args...);
	}

	template<typename... Args>
	void Log(Args... args)
	{
		std::ostringstream out;
		_construct_string_from_args(out, args...);
		LogList.push_back(out.str());
	}

	__declspec(dllexport) void ShowLog(const char* filePath)
	{
		while (!LogList.empty())
		{
			std::string outputString = LogList.front();
			std::cout << outputString << std::endl;
			
			FileOut.open(filePath, std::ios::app);
			FileOut << outputString << std::endl;
			FileOut.close();
			
			LogList.pop_front();
		}
	}
}