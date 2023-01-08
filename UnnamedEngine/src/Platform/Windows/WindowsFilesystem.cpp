#include "uepch.hpp"
#include "Core/Filesystem.hpp"

#include <Windows.h>
#include <shlobj.h>
#include <codecvt>
#include <atlbase.h>
#include <atlconv.h>
#include <sstream>

namespace UE
{
    UEPath Filesystem::m_InternalPath = "Internal/";
    UEPath Filesystem::m_AssetsPath = "Assets/";
    UEPath Filesystem::m_UserDataFolderPath = "";

    UEResult<> Filesystem::Init()
    {
        return UEResult<>::Success;
    }

    UEResult<UEPath> Filesystem::SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath, Filesystem::Target target)
    {
        return UEResult<>::Success;
    }

    UEResult<UEBool> Filesystem::Exists(const UEPath& path, Filesystem::Path enginePath, Filesystem::Target target)
    {
        return UEResult<>::Success;
    }

    UEResult<UEBool> Filesystem::MakeSure(const UEPath& path, Filesystem::Path enginePath, Filesystem::Target target)
    {
        return UEResult<>::Success;
    }

    UEResult<UEBool> Filesystem::Write(const UEPath& path, const UEString& data, Filesystem::Path enginePath)
    {
        return UEResult<>::Success;
    }

    UEResult<UEString> Filesystem::Read(const UEPath& path, Filesystem::Path enginePath)
    {
        return UEResult<>::Success;
    }

    UEResult<UEBool> Filesystem::Delete(const UEPath& path, Filesystem::Path enginePath, Filesystem::Target target)
    {
        return UEResult<>::Success;
    }
}