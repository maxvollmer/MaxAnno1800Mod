

/*
"D:\Work\Anno1800\quickbms+1800Script\quickbms_4gb_files.exe" -d -w -r "D:\Work\Anno1800\quickbms+1800Script\1800.bms" "E:\Spiele\Ubisoft\Anno 1800\maindata\data0.rda" "D:\Work\Anno1800\quickbms+1800Script\maindata"
"D:\Work\Anno1800\quickbms+1800Script\quickbms_4gb_files.exe" -d -w -r "D:\Work\Anno1800\quickbms+1800Script\1800.bms" "E:\Spiele\Ubisoft\Anno 1800\maindata\data10.rda" "D:\Work\Anno1800\quickbms+1800Script\maindata"
*/


#include "pch.h"
#include "Mod.h"
#include "PathHelper.h"
#include "CommandHelper.h"
#include "Constants.h"
#include "InputHelper.h"
#include "XMLToolKit.h"
#include "ModState.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace MaxAnno1800Mod;

Mod::Mod()
{
	PrintHeader();
	GetLocations();
	ExportGameData();
	InitModState();
}

Mod::~Mod()
{
	MaxAnno1800Mod::PathHelper::RemoveTemporaryFolder(m_tempFolder);
}

void Mod::DebugPrintLocations()
{
#ifdef _DEBUG
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Mod Location: " << m_modLocation << std::endl;
	std::cout << "Anno 1800 Install Location: " << m_anno1800InstallLocation << std::endl;
	std::cout << "Temporary Folder Location: " << m_tempFolder << std::endl;
	std::cout << "quickbms Executable Location: " << m_quickbmsExe << std::endl;
	std::cout << "quickbms 1800 script Location: " << m_quickbms1800Script << std::endl;
	std::cout << "Anno 1800 data0.rda Location: " << m_anno1800data0Location << std::endl;
	std::cout << "Anno 1800 data10.rda Location: " << m_anno1800data10Location << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
#endif
}

void Mod::GetLocations()
{
	m_modLocation = MaxAnno1800Mod::PathHelper::FindModLocation();
	if (!MaxAnno1800Mod::PathHelper::IsValidFolder(m_modLocation))
	{
		std::cerr << "Invalid Mod Location, aborting: " << m_modLocation << std::endl;
		std::exit(-1);
	}

	m_quickbmsExe = m_modLocation;
	m_quickbmsExe.append("quickbms").append("quickbms_4gb_files.exe");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_quickbmsExe))
	{
		std::cerr << "Couldn't find quickbms/quickbms_4gb_files.exe in mod folder, make sure you don't run this mod from an archive." << std::endl;
		std::exit(-1);
	}

	m_quickbms1800Script = m_modLocation;
	m_quickbms1800Script.append("quickbms").append("1800.bms");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_quickbms1800Script))
	{
		std::cerr << "Couldn't find quickbms/1800.bms in mod folder, make sure you don't run this mod from an archive." << std::endl;
		std::exit(-1);
	}

	m_anno1800InstallLocation = MaxAnno1800Mod::PathHelper::FindAnno1800InstallLocation();
	if (!MaxAnno1800Mod::PathHelper::IsValidFolder(m_anno1800InstallLocation))
	{
		std::cerr << "Invalid Anno 1800 Install Location, aborting: " << m_anno1800InstallLocation << std::endl;
		std::exit(-1);
	}

	m_anno1800data0Location = m_anno1800InstallLocation;
	m_anno1800data0Location.append("maindata").append("data0.rda");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data0Location))
	{
		std::cerr << "Couldn't find maindata/data0.rda in Anno 1800 game folder, make sure you have selected the correct game folder." << std::endl;
		std::exit(-1);
	}

	m_anno1800data10Location = m_anno1800InstallLocation;
	m_anno1800data10Location.append("maindata").append("data10.rda");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data10Location))
	{
		std::cerr << "Couldn't find maindata/data10.rda in Anno 1800 game folder, make sure you have selected the correct game folder." << std::endl;
		std::exit(-1);
	}

	m_tempFolder = MaxAnno1800Mod::PathHelper::GetTemporaryFolderLocation();
	if (!MaxAnno1800Mod::PathHelper::IsValidFolder(m_tempFolder))
	{
		std::cerr << "Couldn't create temporary folder, aborting." << std::endl;
		std::exit(-1);
	}
}

void Mod::PrintHeader()
{
	std::cout << "**************************************************************************************" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "MaxAnno1800Mod 0.0.1 by Max Vollmer (https://github.com/maxvollmer/MaxAnno1800Mod)" << std::endl;
	std::cout << "* " << " - Adds extended zoom." << std::endl;
	std::cout << "* " << " - Adds square ornament that was missing in the original game." << std::endl;
	std::cout << "* " << " - Enables club ornaments (including chess tables for those who missed the beta)." << std::endl;
	std::cout << "* " << " - (Cheat) Gives unlimited access to all World's Fair ornaments." << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "quickbms by Luigi Auriemma (http://quickbms.com)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "1800.bms script file by kskudlik (https://github.com/kskudlik/Anno-1800-RDA-Extractor)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "DllExport by Denis Kuzmin (https://github.com/3F/DllExport)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "Mod might break with upcoming game updates." << std::endl;
	std::cout << "* " << "Use this mod at your own risk." << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "Anno 1800 and all related trademarks belong to Ubisoft." << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "**************************************************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void Mod::BackupGameData()
{
	auto anno1800data0BackupLocation = m_anno1800data0Location;
	anno1800data0BackupLocation.concat(".backup");

	auto anno1800data10BackupLocation = m_anno1800data10Location;
	anno1800data10BackupLocation.concat(".backup");

	if (std::filesystem::exists(anno1800data0BackupLocation) && std::filesystem::exists(anno1800data10BackupLocation))
	{
		std::cout << "Found backups for Anno 1800 game files." << std::endl << std::endl;
		return;
	}

	if (!InputHelper::GetYesNoResponse("Create backups of game files? (y/n) This is recommended, but requires about 3.67 GB of disk space and might take a while."))
	{
		std::cout << "Creation of backups skipped per user request." << std::endl << std::endl;
		return;
	}

	if (!std::filesystem::exists(anno1800data0BackupLocation))
	{
		std::cout << "Creating backup for Anno 1800 maindata/data0.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(m_anno1800data0Location, anno1800data0BackupLocation);
			std::cout << "Backup for Anno 1800 maindata/data0.rda game file successfully created." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Backup failed, error message: " << e.what() << std::endl;
		}
	}

	if (!std::filesystem::exists(anno1800data10BackupLocation))
	{
		std::cout << "Creating backup for Anno 1800 maindata/data10.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(m_anno1800data10Location, anno1800data10BackupLocation);
			std::cout << "Backup for Anno 1800 maindata/data10.rda game file successfully created." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Backup failed, error message: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << std::endl;
}

void Mod::RestoreBackup()
{
	auto anno1800data0BackupLocation = m_anno1800data0Location;
	anno1800data0BackupLocation.concat(".backup");

	auto anno1800data10BackupLocation = m_anno1800data10Location;
	anno1800data10BackupLocation.concat(".backup");

	if (MaxAnno1800Mod::PathHelper::IsValidFile(anno1800data0BackupLocation))
	{
		std::cout << "Restoring backup for Anno 1800 maindata/data0.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(anno1800data0BackupLocation, m_anno1800data0Location, std::filesystem::copy_options::overwrite_existing);
			std::cout << "Anno 1800 maindata/data0.rda game file successfully restored." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Restore failed, error message: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "No backup for maindata/data0.rda game file found, can't restore." << std::endl;
	}

	if (MaxAnno1800Mod::PathHelper::IsValidFile(anno1800data10BackupLocation))
	{
		std::cout << "Restoring backup for Anno 1800 maindata/data10.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(anno1800data10BackupLocation, m_anno1800data10Location, std::filesystem::copy_options::overwrite_existing);
			std::cout << "Anno 1800 maindata/data10.rda game file successfully restored." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Restore failed, error message: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "No backup for maindata/data10.rda game file found, can't restore." << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void Mod::ExportGameData()
{
	// "D:\Work\Anno1800\quickbms+1800Script\quickbms.exe"
	// -d -o -f "data/config/engine/enginesettings/default.xml"
	// "D:\Work\Anno1800\quickbms+1800Script\1800.bms"
	// "E:\Spiele\Ubisoft\Anno 1800\maindata\data0.rda"
	// "D:\Work\Anno1800\quickbms+1800Script\test"
	BackupGameData();

	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -o -Q -Y -f ";
		command << '"' << Constants::ViewDistanceSettings << ',' << Constants::CameraSettings << ',' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data0Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -o -Q -Y -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data10Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	m_anno1800data0ViewDistanceSettingsLocation = m_tempFolder;
	m_anno1800data0ViewDistanceSettingsLocation.append("data0.rda").append(Constants::ViewDistanceSettings);
	try
	{
		m_anno1800data0ViewDistanceSettingsLocation = std::filesystem::canonical(m_anno1800data0ViewDistanceSettingsLocation);
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "bla: " << e.what() << std::endl;
	}
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data0ViewDistanceSettingsLocation))
	{
		std::cerr << "Couldn't extract enginesettings/default.xml from maindata/data0.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data0CameraSettingsLocation = m_tempFolder;
	m_anno1800data0CameraSettingsLocation.append("data0.rda").append(Constants::CameraSettings);
	m_anno1800data0CameraSettingsLocation = std::filesystem::canonical(m_anno1800data0CameraSettingsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data0CameraSettingsLocation))
	{
		std::cerr << "Couldn't extract camera.xml from maindata/data0.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data0AssetsLocation = m_tempFolder;
	m_anno1800data0AssetsLocation.append("data0.rda").append(Constants::Assets);
	m_anno1800data0AssetsLocation = std::filesystem::canonical(m_anno1800data0AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data0AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data0.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data10AssetsLocation = m_tempFolder;
	m_anno1800data10AssetsLocation.append("data10.rda").append(Constants::Assets);
	m_anno1800data10AssetsLocation = std::filesystem::canonical(m_anno1800data10AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data10AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data10.rda, aborting." << std::endl;
		std::exit(-1);
	}
}

void Mod::ImportGameData()
{
	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -f ";
		command << '"' << Constants::ViewDistanceSettings << ',' << Constants::CameraSettings << ',' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data0Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data10Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}
}

void Mod::ApplyAction(ModAction action)
{
	switch (action)
	{
	case ModAction::INSTALL_ALL:
		XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, true);
		XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, true);
		XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, true);
		XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, true);
		break;
	case ModAction::UNINSTALL_ALL:
		XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, false);
		XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, false);
		XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, false);
		XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, false);
		break;
	case ModAction::TOGGLE_ZOOM:
		XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, !ModState::IsZoomInstalled);
		break;
	case ModAction::TOGGLE_SQUARE_ORNAMENT:
		XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, !ModState::IsSquareOrnamentInstalled);
		break;
	case ModAction::TOGGLE_CLUB_ORNAMENTS:
		XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, !ModState::AreClubOrnamentsInstalled);
		break;
	case ModAction::TOGGLE_CHEAT_ORNAMENTS:
		XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation, !ModState::AreCheatOrnamentsInstalled);
		break;

	case ModAction::RESTORE_BACKUP:
		RestoreBackup();
		break;
	case ModAction::APPLY:
		ImportGameData();
		break;

	case ModAction::CANCEL:
	case ModAction::INVALID:
	default:
		break;
	}

	InitModState();
}

void Mod::InitModState()
{
	ModState::IsZoomInstalled = XMLToolKit::Instance()->IsZoomInstalled(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation);
	ModState::IsSquareOrnamentInstalled = XMLToolKit::Instance()->IsSquareOrnamentInstalled(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation);
	ModState::AreClubOrnamentsInstalled = XMLToolKit::Instance()->AreClubOrnamentsInstalled(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation);
	ModState::AreCheatOrnamentsInstalled = XMLToolKit::Instance()->AreCheatOrnamentsInstalled(m_anno1800data0AssetsLocation, m_anno1800data10AssetsLocation);
}
