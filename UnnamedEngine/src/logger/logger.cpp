#include "Logger.h"

namespace UE 
{
	namespace Logger
	{
		std::ofstream _ue_log_file_out = {};
		std::list<std::string> _ue_log_list = {};
		std::mutex _m = {};
	}
}