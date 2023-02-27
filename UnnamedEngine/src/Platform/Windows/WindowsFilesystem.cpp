#include "Core/Filesystem.hpp"

namespace UE
{
    UEPath Filesystem::m_InternalPath = "./Internal/";
    UEPath Filesystem::m_AssetsPath = "./Assets/";
    UEPath Filesystem::m_UserDataFolderPath = "";

    //UEResult<UEPath> Filesystem::SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath, Filesystem::Target target)
    //{
    //    return UEResult<>::Success;
    //}
}