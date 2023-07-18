#include "Core/PlatformIndependenceLayer/Filesystem.hpp"

namespace UE
{
    UEPath Filesystem::s_InternalPath = "./env/Internal/";
    UEPath Filesystem::s_AssetsPath   = "./env/Assets/";
    UEPath Filesystem::s_UserDataPath = "";

    //UEResult<UEPath> Filesystem::SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath, Filesystem::Target target)
    //{
    //    return UEResult<>::Success;
    //}

    UEResult<> Filesystem::SetUserDataPath()
    {
        if(MakeSure("./env/TempUserData", Filesystem::Path::UserData, Filesystem::Target::Directory))
        {
            UE_LOG_CORE_ERROR("Failed to create user data directory!");
            return UEResult<>::Error;
        }

        s_UserDataPath = "./env/TempUserData/";

        return UEResult<>::Success;
    }
}