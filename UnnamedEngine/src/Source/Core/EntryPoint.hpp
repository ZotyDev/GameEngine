#pragma once
#include "Core/Base.hpp"

#if defined(UE_PLATFORM_WINDOWS) || \
    defined(UE_PLATFORM_WEB)
    extern UE::Application* UE::CreateApplication();

    int main(int argc, char** argv)
    {
        UE_LOG_INIT();

        auto App = UE::CreateApplication();
        App->Run();
        delete App;

        UE_LOG_CORE_INFO("Everything went ok! See you again soon :D {}", "test");

        return 0;
    }

#endif