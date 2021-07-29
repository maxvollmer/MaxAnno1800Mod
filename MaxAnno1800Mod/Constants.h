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

namespace MaxAnno1800Mod
{
	namespace Constants
	{
		constexpr const static char* ViewDistanceSettings = "data/config/engine/enginesettings/default.xml";
		constexpr const static char* CameraSettings = "data/config/game/camera.xml";
		constexpr const static char* Assets = "data/config/export/main/asset/assets.xml";
	}

	enum class ModAction : char
	{
		INVALID = 0,

		INSTALL_ALL = 'i',
		UNINSTALL_ALL = 'u',

		TOGGLE_ZOOM = '1',
		TOGGLE_SQUARE_ORNAMENT = '2',
		TOGGLE_CITY_ORNAMENTS = '3',
		TOGGLE_CLUB_ORNAMENTS = '4',
		TOGGLE_EXTRA_ORNAMENTS = '5',
		TOGGLE_VISUALOBJECTS_ORNAMENTS = '6',
		TOGGLE_CHEAT_ORNAMENTS = '7',
		TOGGLE_ORNAMENT_BOOST = '8',

		RESTORE_BACKUP = 'r',
		CANCEL = 'c',
		APPLY = 'a',

		TEST = 't'
	};
}
