#include "uepch.hpp"
#include "Core/Filesystem.hpp"

namespace UE
{
    UEPath Filesystem::m_InternalPath = "Internal/";
    UEPath Filesystem::m_AssetsPath = "Assets/";
    UEPath Filesystem::m_UserDataFolderPath = "";

    std::error_code Error;

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
        UEPath FinalPath;
        switch (enginePath)
        {
            default:
            case Filesystem::Path::Assets:
            {
                FinalPath = m_AssetsPath / path;
                break;
            }
            case Filesystem::Path::Internal:
            {
                FinalPath = m_InternalPath / path;
                break;
            }
            case Filesystem::Path::UserDataFolder:
            {
                FinalPath = m_UserDataFolderPath / path;
                break;
            }
        }

        UEResult<UEBool> Result(std::filesystem::exists(FinalPath, Error));
        if (!Result.Result)
        {

        }

        return Result;
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