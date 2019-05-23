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
#include "XMLToolKit.h"

using namespace MaxAnno1800Mod;

std::unique_ptr<XMLToolKit> XMLToolKit::m_instance = std::unique_ptr<XMLToolKit>(new XMLToolKit{});

XMLToolKit::XMLToolKit()
{
	HMODULE hXMLToolkitModule = LoadLibraryA("MaxAnno1800ModXMLToolkit.dll");

	_IsZoomInstalled = reinterpret_cast<StateCallback2>(GetProcAddress(hXMLToolkitModule, "IsZoomInstalled"));
	_IsSquareOrnamentInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "IsSquareOrnamentInstalled"));
	_AreCityOrnamentsInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreCityOrnamentsInstalled"));
	_AreClubOrnamentsInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreClubOrnamentsInstalled"));
	_AreCheatOrnamentsInstalled = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreCheatOrnamentsInstalled"));
	_AreVisualObjectsOrnaments = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreVisualObjectsOrnaments"));
	_AreOrnamentsBoosted = reinterpret_cast<StateCallback>(GetProcAddress(hXMLToolkitModule, "AreOrnamentsBoosted"));

	_ToggleZoom = reinterpret_cast<InstallCallback2>(GetProcAddress(hXMLToolkitModule, "ToggleZoom"));
	_ToggleSquareOrnament = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleSquareOrnament"));
	_ToggleCityOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleCityOrnaments"));
	_ToggleClubOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleClubOrnaments"));
	_ToggleCheatOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleCheatOrnaments"));
	_ToggleVisualObjectsOrnaments = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleVisualObjectsOrnaments"));
	_ToggleOrnamentBoost = reinterpret_cast<InstallCallback>(GetProcAddress(hXMLToolkitModule, "ToggleOrnamentBoost"));

	_ApplyChanges = reinterpret_cast<ApplyChangesCallback>(GetProcAddress(hXMLToolkitModule, "ApplyChanges"));
}


bool XMLToolKit::IsZoomInstalled(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile) const
{
	return _IsZoomInstalled((void*)pViewDistanceSettingsFile.string().data(), (void*)pCameraSettingsFile.string().data()) != 0;
}

bool XMLToolKit::IsSquareOrnamentInstalled(const std::filesystem::path& pdataAssetsLocation) const
{
	return _IsSquareOrnamentInstalled((void*)pdataAssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreCityOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const
{
	return _AreCityOrnamentsInstalled((void*)pdataAssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreClubOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const
{
	return _AreClubOrnamentsInstalled((void*)pdataAssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreCheatOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const
{
	return _AreCheatOrnamentsInstalled((void*)pdataAssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreVisualObjectsOrnaments(const std::filesystem::path& pdataAssetsLocation) const
{
	return _AreVisualObjectsOrnaments((void*)pdataAssetsLocation.string().data()) != 0;
}

bool XMLToolKit::AreOrnamentsBoosted(const std::filesystem::path& pdataAssetsLocation) const
{
	return _AreOrnamentsBoosted((void*)pdataAssetsLocation.string().data()) != 0;
}


void XMLToolKit::ToggleZoom(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile, bool install) const
{
	_ToggleZoom((void*)pViewDistanceSettingsFile.string().data(), (void*)pCameraSettingsFile.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleSquareOrnament(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleSquareOrnament((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleCityOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleCityOrnaments((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleClubOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleClubOrnaments((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleCheatOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleCheatOrnaments((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleVisualObjectsOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleVisualObjectsOrnaments((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}

void XMLToolKit::ToggleOrnamentBoost(const std::filesystem::path& pdataAssetsLocation, bool install) const
{
	_ToggleOrnamentBoost((void*)pdataAssetsLocation.string().data(), install ? 1 : 0);
}


void XMLToolKit::ApplyChanges(const std::filesystem::path& pXMLFile) const
{
	_ApplyChanges((void*)pXMLFile.string().data());
}
