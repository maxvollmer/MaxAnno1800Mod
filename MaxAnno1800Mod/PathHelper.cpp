/*
**************************************************************************************
*
* MaxAnno1800Mod 0.0.1 by Max Vollmer (https://github.com/maxvollmer/MaxAnno1800Mod)
*  - Adds extended zoom.
*  - Adds square ornament that was missing in the original game.
*  - Enables hidden city ornaments.
*  - Enables club ornaments (including pre-order statue and open-beta chess tables).
*  - (Experimental) Turns some visual buildings into ornamental buildings that can be built.
*  - (Cheat) Gives unrestricted access to all World Fair ornaments.
*  - (Cheat) Boosts attractiveness of ornaments based on their building cost.
*
* License: CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/)
*
* Each feature can be enabled or disabled individually.
*
* quickbms by Luigi Auriemma (http://quickbms.com)
*
* 1800.bms script file by kskudlik (https://github.com/kskudlik/Anno-1800-RDA-Extractor)
*
* DllExport by Denis Kuzmin (https://github.com/3F/DllExport)
*
* Mod might break with upcoming game updates.
* No warranties whatsoever. Always backup your game files. Use this mod at your own risk.
*
* Anno 1800 and all related trademarks belong to Ubisoft.
*
**************************************************************************************
*/

#include "pch.h"
#include "PathHelper.h"
#include "InputHelper.h"
#include "UUIDHelper.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <limits>

using namespace MaxAnno1800Mod;

std::filesystem::path PathHelper::FindAnno1800InstallLocation()
{
	auto anno1800InstallLocation = GetAnno1800InstallLocationFromRegistry();

	bool response = false;
	while (!response)
	{
		if (!IsValidFolder(anno1800InstallLocation))
		{
			std::cout << "Couldn't detect Anno 1800 Install Location, please select location manually." << std::endl;
		}
		else
		{
			response = InputHelper::GetYesNoResponse("Is this your Anno 1800 Install Location? (y/n): " + anno1800InstallLocation.string());
			if (!response)
			{
				std::cout << "Please select new location." << std::endl;
				anno1800InstallLocation = "";
			}
		}
		if (!IsValidFolder(anno1800InstallLocation))
		{
			anno1800InstallLocation = AskUserForAnno1800Location();
		}
	}

	return anno1800InstallLocation;
}

std::filesystem::path PathHelper::GetAnno1800InstallLocationFromRegistry()
{
	HKEY hKeyUninstall;
	auto result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ENUMERATE_SUB_KEYS, &hKeyUninstall);

	if (result != ERROR_SUCCESS)
	{
		std::cerr << "Error trying to open registry: " << result << std::endl;
		return {};
	}

	char name[1024]{ 0 };
	DWORD nameLength = 1024;
	int index = 0;
	while ((result = RegEnumKeyExA(hKeyUninstall, index++, name, &nameLength, NULL, NULL, NULL, NULL)) != ERROR_NO_MORE_ITEMS)
	{
		nameLength = 1024;

		if (result == ERROR_MORE_DATA)
			continue;

		if (result != ERROR_SUCCESS)
		{
			std::cerr << "Error trying to iterate registry: " << result << std::endl;
			return {};
		}

		char displayName[1024]{ 0 };
		DWORD displayNameLength = 1024;
		char installLocation[1024]{ 0 };
		DWORD installLocationLength = 1024;
		if (ERROR_SUCCESS == RegGetValueA(hKeyUninstall, name, "DisplayName", RRF_RT_REG_SZ, NULL, &displayName, &displayNameLength)
			&& ERROR_SUCCESS == RegGetValueA(hKeyUninstall, name, "InstallLocation", RRF_RT_REG_SZ, NULL, &installLocation, &installLocationLength))
		{
			if (std::string{ "Anno 1800" } == displayName)
			{
				return std::filesystem::canonical(std::filesystem::path{ installLocation });
			}
		}
	}

	return {};
}

std::filesystem::path PathHelper::AskUserForAnno1800Location()
{
	HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to initialize COM library: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	IFileDialog *pfd;
	result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pfd));
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to create folder dialog: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	std::shared_ptr<IFileDialog> pFileDialog(pfd, [](IFileDialog* pfd) { pfd->Release(); });

	DWORD dwOptions;
	result = pFileDialog->GetOptions(&dwOptions);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to get folder dialog options: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	result = pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to set folder dialog options: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	result = pFileDialog->Show(NULL);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to show folder dialog: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	IShellItem *psi;
	result = pFileDialog->GetResult(&psi);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to get result from folder dialog: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	std::shared_ptr<IShellItem> pShellItem(psi, [](IShellItem* psi) { psi->Release(); });

	wchar_t* path = nullptr;
	result = pShellItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &path);
	if (!SUCCEEDED(result))
	{
		std::wcerr << L"Error trying to get path from folder dialog result: " << _com_error{ result }.ErrorMessage() << std::endl;
		return {};
	}

	return std::filesystem::canonical(std::filesystem::path{ path });
}

std::filesystem::path PathHelper::FindModLocation()
{
	std::string path;
	path.resize(1024);
	while (path.size() <= GetModuleFileNameA(NULL, path.data(), path.size()))
	{
		path.resize(path.size() + 1024);
	}
	return std::filesystem::canonical(std::filesystem::path{ path }.parent_path());
}

bool PathHelper::IsValidFolder(const std::filesystem::path& path)
{
	return !path.empty() && path.is_absolute() && std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool PathHelper::IsValidFile(const std::filesystem::path& path)
{
	return !path.empty() && path.is_absolute() && std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

std::filesystem::path PathHelper::GetTemporaryFolderLocation()
{
	std::filesystem::path result;
	const auto sysTempDir = std::filesystem::temp_directory_path();
	do
	{
		std::string randomFolderName = "MaxAnno1800Mod_" + UUIDHelper::GetRandomUUID();
		result = sysTempDir;
		result.append(randomFolderName);
	}
	while (!std::filesystem::create_directory(result));

	return std::filesystem::canonical(result);
}

void PathHelper::RemoveTemporaryFolder(const std::filesystem::path& path)
{
	std::filesystem::remove_all(path);
}
