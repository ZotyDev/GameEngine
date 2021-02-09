#pragma once

#include "core.h"

namespace UE
{
	namespace Logger
	{
		extern std::ofstream _ue_log_file_out;
		extern std::list<std::string> _ue_log_list;
		extern std::mutex _m;

		inline void _ue_log_construct(std::ostringstream& out, bool arg)
		{
			out << (arg ? "true" : "false");
		};
		
		inline void _ue_log_construct(std::ostringstream& out, short int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, unsigned short int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, unsigned int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, long int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, unsigned long int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, long long int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, unsigned long long int arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, signed char arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, unsigned char arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, char arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, wchar_t arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, float arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, double arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, long double arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, const char* arg)
		{
			out << arg;
		};
		
		inline void _ue_log_construct(std::ostringstream& out, std::string arg)
		{
			out << arg;
		};

		template<typename T, typename... Args>
		inline void _ue_log_construct(std::ostringstream& out, T arg, Args... args)
		{
			out << arg;
			_ue_log_construct(out, args...);
		};

		template<typename... Args>
		inline void _ue_log_construct(std::ostringstream& out, bool arg, Args... args)
		{
			out << arg ? "true" : "false";
			_ue_log_construct(out, args...);
		};

		template<typename... Args>
		inline void ue_log(Args... args)
		{
			std::ostringstream out;
			_ue_log_construct(out, args...);
			std::lock_guard<std::mutex> lock(_m);
			_ue_log_list.push_back(out.str());
		};

		UE_API inline void ShowLog(const char* filePath)
		{
			while (!_ue_log_list.empty())
			{
				std::string outputString = _ue_log_list.front();
				std::cout << outputString << std::endl;

				_ue_log_file_out.open(filePath, std::ios::app);
				_ue_log_file_out << outputString << std::endl;
				_ue_log_file_out.close();

				_ue_log_list.pop_front();
			}
		}
	}
}