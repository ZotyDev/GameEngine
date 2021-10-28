#pragma once
#include "Core/Base.h"

#ifdef UE_PLATFORM_WINDOWS

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv)
{
	UE::Log::Init();

	auto app = UE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

#ifdef UE_PLATFORM_ANDROID

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