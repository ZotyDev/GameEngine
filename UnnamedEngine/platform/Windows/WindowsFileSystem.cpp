#include "uepch.h"
#include "Windows/WindowsFileSystem.h"

#include <Windows.h>
#include <ShObjIdl.h>
#include <codecvt>

namespace UE
{
	WindowsFileSystem::WindowsFileSystem()
	{}

	WindowsFileSystem::~WindowsFileSystem()
	{}

	void WindowsFileSystem::Init()
	{

	}

	UEBool WindowsFileSystem::DoesFileExists(const UEPath& path)
	{
		return std::filesystem::exists(path);
	}

	UEResult WindowsFileSystem::ReadToBuffer(const UEPath& path, UEString& buffer)
	{
		if (DoesFileExists(path) == false)
		{
			UE_CORE_ERROR("Failed to read {0}: file not found", path);
			return UEResult::Error;
		}

		std::ifstream SourceIfstream;

		SourceIfstream.open(path);
		if (SourceIfstream.is_open() == false)
		{
			UE_CORE_ERROR("Failed to read {0}: could not open file", path);
			return UEResult::Error;
		}

		std::stringstream SourceStringStream;
		SourceStringStream << SourceIfstream.rdbuf();

		buffer = SourceStringStream.str();

		SourceIfstream.close();

		return UEResult::Success;
	}

	UEBool WindowsFileSystem::FileSelectorDialog(UEPath& receivedPath, UEBool folderOnly)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				if (folderOnly)
				{
					pFileOpen->SetOptions(FOS_PICKFOLDERS);
				}

				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
							receivedPath = convert.to_bytes(pszFilePath);

							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				else
				{
					return false;
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}

		return true;
	}

	UEBool WindowsFileSystem::FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				COMDLG_FILTERSPEC* ComDlgFS = new COMDLG_FILTERSPEC[filters.size()];

				for (UEUint32 i = 0; i < filters.size(); i++)
				{
					PWSTR FirstElement = new WCHAR[filters[i].first.size() + 1];
					PWSTR SecondElement = new WCHAR[filters[i].second.size() + 1];
					std::mbstowcs(FirstElement, filters[i].first.c_str(), filters[i].first.size() + 1);
					std::mbstowcs(SecondElement, filters[i].second.c_str(), filters[i].second.size() + 1);

					ComDlgFS[i].pszName = FirstElement;
					ComDlgFS[i].pszSpec = SecondElement;
				}

				pFileOpen->SetFileTypes(filters.size(), ComDlgFS);

				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
							receivedPath = convert.to_bytes(pszFilePath);

							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				else
				{
					for (UEUint32 i = 0; i < filters.size(); i++)
					{
						delete ComDlgFS[i].pszName;
						delete ComDlgFS[i].pszSpec;
					}
					
					delete[] ComDlgFS;
					return false;
				}

				for (UEUint32 i = 0; i < filters.size(); i++)
				{
					delete ComDlgFS[i].pszName;
					delete ComDlgFS[i].pszSpec;
				}
				
				delete[] ComDlgFS;
				pFileOpen->Release();
			}
			CoUninitialize();
		}

		return true;
	}
}