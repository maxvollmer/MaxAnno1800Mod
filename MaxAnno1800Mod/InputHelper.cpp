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
#include "InputHelper.h"
#include "ModState.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <limits>

using namespace MaxAnno1800Mod;


bool InputHelper::GetYesNoResponse(const std::string& prompt)
{
	std::cout << prompt << std::endl;

	char response = 'n';
	do
	{
		std::cin >> response;
		if (response != 'n' && response != 'N' && response != 'y' && response != 'Y')
		{
			std::cout << "Please enter y for yes or n for no." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (response != 'n' && response != 'N' && response != 'y' && response != 'Y');

	std::cout << std::endl;

	return response == 'y' || response == 'Y';
}

const char* InstallModeFromState(bool installed)
{
	return installed ? "Uninstall" :"Install";
}

void InputHelper::PrintModActionPrompt()
{
	std::cout << "Please select an option: " << std::endl;
	std::cout << std::endl;
	std::cout << " " << char(ModAction::INSTALL_ALL) << " - Install everything" << std::endl;
	std::cout << " " << char(ModAction::UNINSTALL_ALL) << " - Uninstall everything" << std::endl;
	std::cout << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_ZOOM) << " - " << InstallModeFromState(ModState::IsZoomInstalled) << " extended zoom" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_SQUARE_ORNAMENT) << " - " << InstallModeFromState(ModState::IsSquareOrnamentInstalled) << " square ornament" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_CITY_ORNAMENTS) << " - " << InstallModeFromState(ModState::AreCityOrnamentsInstalled) << " city ornaments" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_CLUB_ORNAMENTS) << " - " << InstallModeFromState(ModState::AreClubOrnamentsInstalled) << " club ornaments" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_VISUALOBJECTS_ORNAMENTS) << " - " << InstallModeFromState(ModState::AreVisualObjectsOrnaments) << " visual objects ornaments" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_CHEAT_ORNAMENTS) << " - " << InstallModeFromState(ModState::AreCheatOrnamentsInstalled) << " cheat ornaments" << std::endl;
	std::cout << " " << char(ModAction::TOGGLE_ORNAMENT_BOOST) << " - " << InstallModeFromState(ModState::AreOrnamentsBoosted) << " ornament attractiveness boost" << std::endl;
	std::cout << std::endl;
	std::cout << " " << char(ModAction::RESTORE_BACKUP) << " - Restore backup and quit" << std::endl;
	std::cout << " " << char(ModAction::APPLY) << " - Apply changes and quit" << std::endl;
	std::cout << " " << char(ModAction::CANCEL) << " - Cancel (quit without applying any changes)" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

ModAction InputHelper::PromptModAction()
{
	PrintModActionPrompt();

	ModAction response = ModAction::INVALID;
	do
	{
		char c;
		std::cin >> c;
		response = ModAction(c);
		switch (response)
		{
		case ModAction::RESTORE_BACKUP:
		case ModAction::INSTALL_ALL:
		case ModAction::UNINSTALL_ALL:
		case ModAction::TOGGLE_ZOOM:
		case ModAction::TOGGLE_SQUARE_ORNAMENT:
		case ModAction::TOGGLE_CITY_ORNAMENTS:
		case ModAction::TOGGLE_CLUB_ORNAMENTS:
		case ModAction::TOGGLE_CHEAT_ORNAMENTS:
		case ModAction::TOGGLE_VISUALOBJECTS_ORNAMENTS:
		case ModAction::TOGGLE_ORNAMENT_BOOST:
		case ModAction::CANCEL:
		case ModAction::APPLY:
		case ModAction::TEST:
			break;
		case ModAction::INVALID:
		default:
			{
				std::cout << "Please enter a valid option from the list above." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				response = ModAction::INVALID;
				break;
			}
		}
	} while (response == ModAction::INVALID);

	return response;
}
