#include "Core/PlatformIndependenceLayer/Filesystem.hpp"

#include <Windows.h>
#include <shlobj.h>
#include <codecvt>
#include <atlbase.h>
#include <atlconv.h>

namespace UE
{
    UEPath Filesystem::s_InternalPath = "./Internal/";
    UEPath Filesystem::s_AssetsPath   = "./Assets/";
    UEPath Filesystem::s_UserDataPath = "";

    //UEResult<UEPath> Filesystem::SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath, Filesystem::Target target)
    //{
    //    return UEResult<>::Success;
    //}

    UEResult<> Filesystem::SetUserDataPath()
    {        
        LPWSTR LocalAppData = NULL;
		HRESULT Result = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &LocalAppData);
		if (SUCCEEDED(Result))
		{
			std::wstringstream ss;
			ss << LocalAppData;
			UEPath LocalAppDataPath(ss.str());
			
			CoTaskMemFree(static_cast<void*>(LocalAppData));

			s_UserDataPath = LocalAppDataPath.string();

			return UEResult<>::Success;
		}
		else
		{
			return UEResult<>::Error;
		}
    }
}