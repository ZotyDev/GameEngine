#pragma once
#include "Core/Base.hpp"

extern UE::Application* UE::CreateApplication(const EntryArgs& args);

#if defined(UE_PLATFORM_WINDOWS) || \
    defined(UE_PLATFORM_LINUX)   || \
    defined(UE_PLATFORM_EMSCRIPTEN)

    int main(int argc, char** argv)
    {
        std::cout << "Entry Point - Creating Logger..." << std::endl;
        UE_LOG_INIT();

        UE_LOG_CORE_INFO("Logger created, creating Application...");

        UE::EntryArgs Args;
        Args.Count = (UE::UEUint32)argc;
        Args.List = std::vector<UE::UEString>(argv, argv + argc);
        auto App = UE::CreateApplication(Args);

        UE_LOG_CORE_INFO("Everything went ok, see you again soon!");

        return 0;
    }

#endif