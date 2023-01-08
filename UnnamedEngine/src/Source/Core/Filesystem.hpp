#pragma once

#include "Core/Base.hpp"

namespace UE
{
    // Todo: Zoty
    // Create a struct to hold the filters of file selector dialog
    class Filesystem
    {
    public:
        enum class Path : UEUint8
        {
            Internal       = 0,
            Assets         = 1,
            UserDataFolder = 2
        };

        enum class Target : UEUint8
        {
            Any    = 0,
            File   = 1,
            Folder = 2
        };

    public:
        static UEResult<> Init();
        static UEResult<UEPath> SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any);
        static UEResult<UEBool> Exists(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any);
        static UEResult<UEBool> MakeSure(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any);
        static UEResult<UEBool> Write(const UEPath& path, const UEString& data, Filesystem::Path enginePath = Filesystem::Path::Assets);
        static UEResult<UEString> Read(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets);
        static UEResult<UEBool> Delete(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any);

    private:
        static UEPath m_InternalPath;
        static UEPath m_AssetsPath;
        static UEPath m_UserDataFolderPath;
    };
}