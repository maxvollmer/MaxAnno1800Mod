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
#pragma once

#include <memory>
#include <filesystem>

namespace MaxAnno1800Mod
{
	class XMLToolKit
	{
	public:

		static const std::unique_ptr<XMLToolKit>& Instance() { return m_instance; }

		bool IsZoomInstalled(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile) const;
		bool IsSquareOrnamentInstalled(const std::filesystem::path& pdataAssetsLocation) const;
		bool AreCityOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const;
		bool AreClubOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const;
		bool AreCheatOrnamentsInstalled(const std::filesystem::path& pdataAssetsLocation) const;
		bool AreVisualObjectsOrnaments(const std::filesystem::path& pdataAssetsLocation) const;
		bool AreOrnamentsBoosted(const std::filesystem::path& pdataAssetsLocation) const;

		void ToggleZoom(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile, bool install) const;
		void ToggleSquareOrnament(const std::filesystem::path& pdataAssetsLocation, bool install) const;
		void ToggleCityOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const;
		void ToggleClubOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const;
		void ToggleCheatOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const;
		void ToggleVisualObjectsOrnaments(const std::filesystem::path& pdataAssetsLocation, bool install) const;
		void ToggleOrnamentBoost(const std::filesystem::path& pdataAssetsLocation, bool install) const;

		void ApplyChanges(const std::filesystem::path& pXMLFile) const;

	private:
		XMLToolKit();

		using StateCallback = int(__stdcall *)(void*);
		using InstallCallback = void(__stdcall *)(void*, int);
		using StateCallback2 = int(__stdcall *)(void*, void*);
		using InstallCallback2 = void(__stdcall *)(void*, void*, int);
		using ApplyChangesCallback = void(__stdcall *)(void*);

		StateCallback2 _IsZoomInstalled{ nullptr };
		StateCallback _IsSquareOrnamentInstalled{ nullptr };
		StateCallback _AreCityOrnamentsInstalled{ nullptr };
		StateCallback _AreClubOrnamentsInstalled{ nullptr };
		StateCallback _AreCheatOrnamentsInstalled{ nullptr };
		StateCallback _AreVisualObjectsOrnaments{ nullptr };
		StateCallback _AreOrnamentsBoosted{ nullptr };

		InstallCallback2 _ToggleZoom{ nullptr };
		InstallCallback _ToggleSquareOrnament{ nullptr };
		InstallCallback _ToggleCityOrnaments{ nullptr };
		InstallCallback _ToggleClubOrnaments{ nullptr };
		InstallCallback _ToggleCheatOrnaments{ nullptr };
		InstallCallback _ToggleVisualObjectsOrnaments{ nullptr };
		InstallCallback _ToggleOrnamentBoost{ nullptr };

		ApplyChangesCallback _ApplyChanges{ nullptr };

		static std::unique_ptr<XMLToolKit> m_instance;
	};

}
