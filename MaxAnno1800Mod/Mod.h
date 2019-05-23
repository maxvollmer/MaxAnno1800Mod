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

#include <filesystem>
#include "Constants.h"

namespace MaxAnno1800Mod
{
	class Mod
	{
	public:
		Mod();
		~Mod();

		void DebugPrintLocations();

		void ApplyAction(ModAction action);

	private:
		static constexpr const int TEST_TIMES = 4;

		void BackupGameData();
		void PrintHeader();
		void GetLocations();
		void RestoreBackup();
		void InitModState();
		void ExportGameData();
		void ApplyChanges();
		void ImportGameData();

		void RunTest();

		std::filesystem::path m_modLocation;
		std::filesystem::path m_anno1800InstallLocation;
		std::filesystem::path m_tempFolder;

		std::filesystem::path m_quickbmsExe;
		std::filesystem::path m_quickbms1800Script;

		std::filesystem::path m_anno1800data0Location;
		std::filesystem::path m_anno1800data10Location;

		std::filesystem::path m_anno1800data0ViewDistanceSettingsLocation;
		std::filesystem::path m_anno1800data0CameraSettingsLocation;
		std::filesystem::path m_anno1800data10AssetsLocation;
	};
}
