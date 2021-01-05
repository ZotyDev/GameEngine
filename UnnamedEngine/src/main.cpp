#include "core.h"

#include "threadpool/threadpool.h"
#include "logger/logger.h"

#include <Windows.h>

std::list<std::string> LogList;

int main()
{
	ThreadPool pool(6);

	auto f1 = pool.enqueue([] {
		return 1;
	});

	auto f2 = pool.enqueue([] {
		return 1;
	});

	Sleep(100);

	std::cout << f1._Is_ready() << std::endl;

	std::cout << f1.get() + f2.get();

	std::time_t t = std::time(0);

	Logger::Log("this is just a test :)");

	std::ofstream ofs;
	ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	pool.enqueue([] 
	{
		Logger::ShowLog("log.txt");
	});

	return 0;
}