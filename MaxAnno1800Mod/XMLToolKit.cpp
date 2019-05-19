
#include "pch.h"
#include "XMLToolKit.h"

using namespace MaxAnno1800Mod;

std::unique_ptr<XMLToolKit> XMLToolKit::m_instance = std::unique_ptr<XMLToolKit>(new XMLToolKit{});

XMLToolKit::XMLToolKit()
{
	HMODULE hXMLToolkitModule = LoadLibraryA("MaxAnno1800ModXMLToolkit.dll");

	_IsZoomInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "IsZoomInstalled"));
	_IsSquareOrnamentInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "IsSquareOrnamentInstalled"));
	_AreClubOrnamentsInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreClubOrnamentsInstalled"));
	_AreCheatOrnamentsInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreCheatOrnamentsInstalled"));

	_ToggleZoom = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleZoom"));
	_ToggleSquareOrnament = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleSquareOrnament"));
	_ToggleClubOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleClubOrnaments"));
	_ToggleCheatOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleCheatOrnaments"));
}

bool XMLToolKit::IsZoomInstalled(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile) const
{
	return _IsZoomInstalled((void*)pViewDistanceSettingsFile.string().data(), (void*)pCameraSettingsFile.string().data()) != 0;
}

bool XMLToolKit::IsSquareOrnamentInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const
{
	return _IsSquareOrnamentInstalled((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreClubOrnamentsInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const
{
	return _AreClubOrnamentsInstalled((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreCheatOrnamentsInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const
{
	return _AreCheatOrnamentsInstalled((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data()) != 0;
}


void XMLToolKit::ToggleZoom(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile, bool install) const
{
	_ToggleZoom((void*)pViewDistanceSettingsFile.string().data(), (void*)pCameraSettingsFile.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleSquareOrnament(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const
{
	_ToggleSquareOrnament((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleClubOrnaments(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const
{
	_ToggleClubOrnaments((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleCheatOrnaments(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const
{
	_ToggleCheatOrnaments((void*)pdata0AssetsLocation.string().data(), (void*)pdata10AssetsLocation.string().data(), install ? 1 : 0);
}
