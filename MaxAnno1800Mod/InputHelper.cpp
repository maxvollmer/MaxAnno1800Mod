
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
	std::cout << " i - Install everything" << std::endl;
	std::cout << " u - Uninstall everything" << std::endl;
	std::cout << std::endl;
	std::cout << " 1 - " << InstallModeFromState(ModState::IsZoomInstalled) << " extended zoom" << std::endl;
	std::cout << " 2 - " << InstallModeFromState(ModState::IsSquareOrnamentInstalled) << " square ornament" << std::endl;
	std::cout << " 3 - " << InstallModeFromState(ModState::AreClubOrnamentsInstalled) << " club ornaments" << std::endl;
	std::cout << " 4 - " << InstallModeFromState(ModState::AreCheatOrnamentsInstalled) << " cheat ornaments" << std::endl;
	std::cout << std::endl;
	std::cout << " r - Restore backup and quit" << std::endl;
	std::cout << " a - Apply changes and quit" << std::endl;
	std::cout << " c - Cancel (quit without applying any changes)" << std::endl;
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
		case ModAction::TOGGLE_CLUB_ORNAMENTS:
		case ModAction::TOGGLE_CHEAT_ORNAMENTS:
		case ModAction::CANCEL:
		case ModAction::APPLY:
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
