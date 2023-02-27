#pragma once
#include "Core/Base.hpp"

extern UE::Application* UE::CreateApplication();

#if defined(UE_PLATFORM_WINDOWS) || \
    defined(UE_PLATFORM_LINUX)   || \
    defined(UE_PLATFORM_WEB)

    int main(int argc, char** argv)
    {
        UE_LOG_INIT();

        auto App = UE::CreateApplication();

        return 0;
    }

#endif