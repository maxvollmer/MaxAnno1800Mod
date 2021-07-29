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

namespace MaxAnno1800Mod
{
	class PathHelper
	{
	public:
		static std::filesystem::path FindModLocation();
		static std::filesystem::path FindAnno1800InstallLocation();
		static std::filesystem::path GetTemporaryFolderLocation();

		static void RemoveTemporaryFolder(const std::filesystem::path& path);

		static bool IsValidFolder(const std::filesystem::path& path);
		static bool IsValidFile(const std::filesystem::path& path);

	private:
		static std::filesystem::path GetAnno1800InstallLocationFromRegistry();
		static std::filesystem::path AskUserForAnno1800Location();
	};
}
