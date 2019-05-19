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
		TOGGLE_CLUB_ORNAMENTS = '3',
		TOGGLE_CHEAT_ORNAMENTS = '4',

		RESTORE_BACKUP = 'r',
		CANCEL = 'c',
		APPLY = 'a'
	};
}
