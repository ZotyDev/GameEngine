#include "Core/PlatformIndependenceLayer/Filesystem.hpp"

namespace UE
{
    UEPath Filesystem::s_InternalPath = "./env/Internal/";
    UEPath Filesystem::s_AssetsPath   = "./env/Assets/";
    UEPath Filesystem::s_UserDataPath = "";

    UEResult<> Filesystem::SetUserDataPath()
    {
        return UEResult<>::Success;
    }
}