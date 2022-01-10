#pragma once
#include "Core/Base.h"

#if defined(UE_PLATFORM_WINDOWS)

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv)
{
	UE::Log::Init();

	auto app = UE::CreateApplication();
	app->Run();
	delete app;

	UE_CORE_INFO("Everything went ok! See you again :D");

	return 0;
}

#endif

#if defined(UE_PLATFORM_WEB)

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv)
{
	UE::Log::Init();

	auto app = UE::CreateApplication();
	app->Run();
	delete app;

	UE_CORE_INFO("Everything wen ok! See you again :D");

	return 0;
}

#endif

#if defined(UE_PLATFORM_ANDROID)

extern UE::Application* UE::CreateApplication();

extern "C"
{
	void android_main(struct android_app* state);
};

void android_main(struct android_app* android_app)
{
	auto app = UE::CreateApplication();
	app->Run();
	delete app;
}

#endif