#include "core.h"

#include "threadpool/threadpool.h"
#include "logger/logger.h"
#include "time/timeManager.h"

#include <Windows.h>

std::list<std::string> LogList;

int main()
{
	ThreadPool pool(6);

	TimeManager::Update();

	LOG_INFO("Happy ", TimeManager::GetYear(), "!");

	std::ofstream ofs;
	ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	pool.enqueue([] 
	{
		Logger::ShowLog("log.txt");
	});

	return 0;
}