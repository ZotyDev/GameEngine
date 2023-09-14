#include "Core/PlatformIndependenceLayer/Filesystem.hpp"

namespace UE
{
    UEPath Filesystem::s_InternalPath = "./Internal/";
    UEPath Filesystem::s_AssetsPath   = "./Assets/";
    UEPath Filesystem::s_UserDataPath = "";

    UEResult<> Filesystem::SetUserDataPath()
    {
        char* Home = std::getenv("HOME");
        if (Home != nullptr)
        {
            std::stringstream ss;
            ss << Home;
            UEPath HomePath(ss.str());

            s_UserDataPath = HomePath.string();

            return UEResult<>::Success;
        }
        return UEResult<>::Error;
    }
}
