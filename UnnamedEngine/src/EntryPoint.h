#pragma once

#ifdef UE_PLATFORM_WINDOWS

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv)
{
	auto app = UE::CreateApplication();
	app->Run();
	delete app;
}

#endif