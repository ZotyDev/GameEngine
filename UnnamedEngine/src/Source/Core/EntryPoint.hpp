#pragma once
#include "Core/Base.hpp"

#include <csignal>
#include <cstring>

extern UE::Ref<UE::Application> UE::CreateApplication(const EntryArgs& args);

#if defined(UE_PLATFORM_WINDOWS) || \
    defined(UE_PLATFORM_LINUX)   || \
    defined(UE_PLATFORM_EMSCRIPTEN)

    UE::Ref<UE::Application> App;

    // Properly handles SIGINT
    void signal_handler(int signum)
    {
        App->Stop();
        raise(SIGTERM);
    }

    int main(int argc, char** argv)
    {
        std::cout << "Entry Point - Creating Logger..." << std::endl;
        UE_LOG_INIT();

        UE_LOG_CORE_INFO("Logger created, creating Application...");

        // Setup the signal handler
        signal(SIGINT, signal_handler);

        UE::EntryArgs Args;
        Args.Count = (UE::UEUint32)argc;
        Args.List = std::vector<UE::UEString>(argv, argv + argc);

        App = UE::CreateApplication(Args);

        return 0;
    }

#endif