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
#include <algorithm>
#include <random>

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
#ifndef _DEBUG
	MaxAnno1800Mod::PathHelper::RemoveTemporaryFolder(m_tempFolder);
#endif
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

	m_anno1800data14Location = m_anno1800InstallLocation;
	m_anno1800data14Location.append("maindata").append("data14.rda");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data14Location))
	{
		std::cerr << "Couldn't find maindata/data14.rda in Anno 1800 game folder, make sure you have selected the correct game folder." << std::endl;
		std::exit(-1);
	}

	m_anno1800data15Location = m_anno1800InstallLocation;
	m_anno1800data15Location.append("maindata").append("data15.rda");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data15Location))
	{
		std::cerr << "Couldn't find maindata/data15.rda in Anno 1800 game folder, make sure you have selected the correct game folder." << std::endl;
		std::exit(-1);
	}
	m_anno1800data16Location = m_anno1800InstallLocation;
	m_anno1800data16Location.append("maindata").append("data16.rda");
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data16Location))
	{
		std::cerr << "Couldn't find maindata/data16.rda in Anno 1800 game folder, make sure you have selected the correct game folder." << std::endl;
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
	std::cout << "* " << " - Enables hidden city ornaments." << std::endl;
	std::cout << "* " << " - Enables club ornaments (including pre-order statue and open-beta chess tables)." << std::endl;
	std::cout << "* " << " - (Experimental) Turns some visual buildings into ornamental buildings that can be built." << std::endl;
	std::cout << "* " << " - (Cheat) Gives unrestricted access to all World Fair ornaments." << std::endl;
	std::cout << "* " << " - (Cheat) Boosts attractiveness of ornaments based on their building cost." << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "License: CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "Each feature can be enabled or disabled individually." << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "quickbms by Luigi Auriemma (http://quickbms.com)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "1800.bms script file by kskudlik (https://github.com/kskudlik/Anno-1800-RDA-Extractor)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "DllExport by Denis Kuzmin (https://github.com/3F/DllExport)" << std::endl;
	std::cout << "* " << std::endl;
	std::cout << "* " << "Mod might break with upcoming game updates." << std::endl;
	std::cout << "* " << "No warranties whatsoever. Always backup your game files. Use this mod at your own risk." << std::endl;
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

	auto anno1800data14BackupLocation = m_anno1800data14Location;
	anno1800data14BackupLocation.concat(".backup");

	auto anno1800data15BackupLocation = m_anno1800data15Location;
	anno1800data15BackupLocation.concat(".backup");

	auto anno1800data16BackupLocation = m_anno1800data16Location;
	anno1800data16BackupLocation.concat(".backup");

	if (std::filesystem::exists(anno1800data0BackupLocation) && std::filesystem::exists(anno1800data10BackupLocation) && std::filesystem::exists(anno1800data14BackupLocation) && std::filesystem::exists(anno1800data15BackupLocation) && std::filesystem::exists(anno1800data16BackupLocation))
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
	if (!std::filesystem::exists(anno1800data14BackupLocation))
	{
		std::cout << "Creating backup for Anno 1800 maindata/data14.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(m_anno1800data14Location, anno1800data14BackupLocation);
			std::cout << "Backup for Anno 1800 maindata/data14.rda game file successfully created." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Backup failed, error message: " << e.what() << std::endl;
		}
	}

	if (!std::filesystem::exists(anno1800data15BackupLocation))
	{
		std::cout << "Creating backup for Anno 1800 maindata/data15.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(m_anno1800data15Location, anno1800data15BackupLocation);
			std::cout << "Backup for Anno 1800 maindata/data15.rda game file successfully created." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Backup failed, error message: " << e.what() << std::endl;
		}
	}

	if (!std::filesystem::exists(anno1800data16BackupLocation))
	{
		std::cout << "Creating backup for Anno 1800 maindata/data16.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(m_anno1800data15Location, anno1800data16BackupLocation);
			std::cout << "Backup for Anno 1800 maindata/data16.rda game file successfully created." << std::endl;
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

	auto anno1800data14BackupLocation = m_anno1800data14Location;
	anno1800data14BackupLocation.concat(".backup");

	auto anno1800data15BackupLocation = m_anno1800data15Location;
	anno1800data15BackupLocation.concat(".backup");

	auto anno1800data16BackupLocation = m_anno1800data16Location;
	anno1800data16BackupLocation.concat(".backup");

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

	if (MaxAnno1800Mod::PathHelper::IsValidFile(anno1800data14BackupLocation))
	{
		std::cout << "Restoring backup for Anno 1800 maindata/data14.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(anno1800data14BackupLocation, m_anno1800data14Location, std::filesystem::copy_options::overwrite_existing);
			std::cout << "Anno 1800 maindata/data14.rda game file successfully restored." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Restore failed, error message: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "No backup for maindata/data14.rda game file found, can't restore." << std::endl;
	}

	if (MaxAnno1800Mod::PathHelper::IsValidFile(anno1800data15BackupLocation))
	{
		std::cout << "Restoring backup for Anno 1800 maindata/data15.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(anno1800data15BackupLocation, m_anno1800data15Location, std::filesystem::copy_options::overwrite_existing);
			std::cout << "Anno 1800 maindata/data15.rda game file successfully restored." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Restore failed, error message: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "No backup for maindata/data15.rda game file found, can't restore." << std::endl;
	}

	if (MaxAnno1800Mod::PathHelper::IsValidFile(anno1800data16BackupLocation))
	{
		std::cout << "Restoring backup for Anno 1800 maindata/data16.rda game file, please wait." << std::endl;
		try
		{
			std::filesystem::copy(anno1800data16BackupLocation, m_anno1800data15Location, std::filesystem::copy_options::overwrite_existing);
			std::cout << "Anno 1800 maindata/data16.rda game file successfully restored." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Restore failed, error message: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "No backup for maindata/data16.rda game file found, can't restore." << std::endl;
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

	std::cout << "Extracting game data from game folder, please wait..." << std::endl;

	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -o -Q -Y -f ";
		command << '"' << Constants::ViewDistanceSettings << ',' << Constants::CameraSettings << '"' << ' ';
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

	{
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -o -Q -Y -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data14Location;
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
		command << m_anno1800data15Location;
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
		command << m_anno1800data16Location;
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

	m_anno1800data10AssetsLocation = m_tempFolder;
	m_anno1800data10AssetsLocation.append("data10.rda").append(Constants::Assets);
	m_anno1800data10AssetsLocation = std::filesystem::canonical(m_anno1800data10AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data10AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data10.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data14AssetsLocation = m_tempFolder;
	m_anno1800data14AssetsLocation.append("data14.rda").append(Constants::Assets);
	m_anno1800data14AssetsLocation = std::filesystem::canonical(m_anno1800data14AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data14AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data14.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data15AssetsLocation = m_tempFolder;
	m_anno1800data15AssetsLocation.append("data15.rda").append(Constants::Assets);
	m_anno1800data15AssetsLocation = std::filesystem::canonical(m_anno1800data15AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data15AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data15.rda, aborting." << std::endl;
		std::exit(-1);
	}

	m_anno1800data16AssetsLocation = m_tempFolder;
	m_anno1800data16AssetsLocation.append("data16.rda").append(Constants::Assets);
	m_anno1800data16AssetsLocation = std::filesystem::canonical(m_anno1800data16AssetsLocation);
	if (!MaxAnno1800Mod::PathHelper::IsValidFile(m_anno1800data16AssetsLocation))
	{
		std::cerr << "Couldn't extract assets.xml from maindata/data16.rda, aborting." << std::endl;
		std::exit(-1);
	}

	std::cout << "...done extracting game data from game folder." << std::endl << std::endl;
}

void Mod::ImportGameData()
{

	{
		std::cout << "Importing data0.rda" << std::endl;
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -b 20 -f ";
		command << '"' << Constants::ViewDistanceSettings << ',' << Constants::CameraSettings << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data0Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::cout << "Importing data10.rda" << std::endl;
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -b 20 -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data10Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::cout << "Importing data14.rda" << std::endl;
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -b 20 -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data14Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::cout << "Importing data15.rda" << std::endl;
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -b 20 -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data15Location;
		command << ' ';
		command << m_tempFolder;

		CommandHelper::ExecuteCommand(command.str());
	}

	{
		std::cout << "Importing data16.rda" << std::endl;
		std::stringstream command;
		command << m_quickbmsExe;
		command << " -d -w -r -Q -Y -b 20 -f ";
		command << '"' << Constants::Assets << '"' << ' ';
		command << m_quickbms1800Script;
		command << ' ';
		command << m_anno1800data16Location;
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
		{
			if (!ModState::IsZoomInstalled)				XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, true);
			if (!ModState::IsSquareOrnamentInstalled)	XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data10AssetsLocation, true);
			if (!ModState::AreCityOrnamentsInstalled)	XMLToolKit::Instance()->ToggleCityOrnaments(m_anno1800data10AssetsLocation, true);
			if (!ModState::AreClubOrnamentsInstalled)	XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data10AssetsLocation, true);
			if (!ModState::AreExtraOrnamentsInstalled) { XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data14AssetsLocation, true); XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data15AssetsLocation, true); XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data16AssetsLocation, true); }
			if (!ModState::AreVisualObjectsOrnaments)	XMLToolKit::Instance()->ToggleVisualObjectsOrnaments(m_anno1800data10AssetsLocation, true);
			if (!ModState::AreCheatOrnamentsInstalled)	XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data10AssetsLocation, true);
			if (!ModState::AreOrnamentsBoosted)			XMLToolKit::Instance()->ToggleOrnamentBoost(m_anno1800data10AssetsLocation, true);
		}
		break;
	case ModAction::UNINSTALL_ALL:
		{
			if (ModState::IsZoomInstalled)				XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, false);
			if (ModState::IsSquareOrnamentInstalled)	XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data10AssetsLocation, false);
			if (ModState::AreCityOrnamentsInstalled)	XMLToolKit::Instance()->ToggleCityOrnaments(m_anno1800data10AssetsLocation, false);
			if (ModState::AreClubOrnamentsInstalled)	XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data10AssetsLocation, false);
			if (ModState::AreExtraOrnamentsInstalled) { XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data14AssetsLocation, false); XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data15AssetsLocation, false); XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data16AssetsLocation, false); }
			if (ModState::AreVisualObjectsOrnaments)	XMLToolKit::Instance()->ToggleVisualObjectsOrnaments(m_anno1800data10AssetsLocation, false);
			if (ModState::AreCheatOrnamentsInstalled)	XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data10AssetsLocation, false);
			if (ModState::AreOrnamentsBoosted)			XMLToolKit::Instance()->ToggleOrnamentBoost(m_anno1800data10AssetsLocation, false);
		}
		break;

	case ModAction::TOGGLE_ZOOM:
		XMLToolKit::Instance()->ToggleZoom(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation, !ModState::IsZoomInstalled);
		break;
	case ModAction::TOGGLE_SQUARE_ORNAMENT:
		XMLToolKit::Instance()->ToggleSquareOrnament(m_anno1800data10AssetsLocation, !ModState::IsSquareOrnamentInstalled);
		break;
	case ModAction::TOGGLE_CITY_ORNAMENTS:
		XMLToolKit::Instance()->ToggleCityOrnaments(m_anno1800data10AssetsLocation, !ModState::AreCityOrnamentsInstalled);
		break;
	case ModAction::TOGGLE_CLUB_ORNAMENTS:
		XMLToolKit::Instance()->ToggleClubOrnaments(m_anno1800data10AssetsLocation, !ModState::AreClubOrnamentsInstalled);
		break;
	case ModAction::TOGGLE_EXTRA_ORNAMENTS:
		XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data14AssetsLocation, !ModState::AreExtraOrnamentsInstalled);
		XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data15AssetsLocation, !ModState::AreExtraOrnamentsInstalled);
		XMLToolKit::Instance()->ToggleExtraOrnaments(m_anno1800data16AssetsLocation, !ModState::AreExtraOrnamentsInstalled);
		break;
	case ModAction::TOGGLE_VISUALOBJECTS_ORNAMENTS:
		XMLToolKit::Instance()->ToggleVisualObjectsOrnaments(m_anno1800data10AssetsLocation, !ModState::AreVisualObjectsOrnaments);
		break;
	case ModAction::TOGGLE_CHEAT_ORNAMENTS:
		XMLToolKit::Instance()->ToggleCheatOrnaments(m_anno1800data10AssetsLocation, !ModState::AreCheatOrnamentsInstalled);
		break;
	case ModAction::TOGGLE_ORNAMENT_BOOST:
		XMLToolKit::Instance()->ToggleOrnamentBoost(m_anno1800data10AssetsLocation, !ModState::AreOrnamentsBoosted);
		break;

	case ModAction::RESTORE_BACKUP:
		RestoreBackup();
		break;
	case ModAction::APPLY:
		ApplyChanges();
		break;

	case ModAction::TEST:
		RunTest();
		break;

	case ModAction::CANCEL:
	case ModAction::INVALID:
	default:
		break;
	}

	std::cout << std::endl;

	if (action != ModAction::RESTORE_BACKUP && action != ModAction::CANCEL && action != ModAction::APPLY)
	{
		InitModState();
	}
}

void Mod::ApplyChanges()
{
	std::cout << "Applying changes, this might take a while..." << std::endl;
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data0ViewDistanceSettingsLocation);
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data0CameraSettingsLocation);
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data10AssetsLocation);
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data14AssetsLocation);
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data15AssetsLocation);
	XMLToolKit::Instance()->ApplyChanges(m_anno1800data16AssetsLocation);
	std::cout << "...done applying changes, importing game files into game..." << std::endl;
	ImportGameData();
	std::cout << "...done importing game files into game." << std::endl << std::endl;
}

void Mod::InitModState()
{
	std::cout << "Getting state of things, this might take a while..." << std::endl;
	ModState::IsZoomInstalled = XMLToolKit::Instance()->IsZoomInstalled(m_anno1800data0ViewDistanceSettingsLocation, m_anno1800data0CameraSettingsLocation);

	ModState::IsSquareOrnamentInstalled = XMLToolKit::Instance()->IsSquareOrnamentInstalled(m_anno1800data10AssetsLocation);

	ModState::AreCityOrnamentsInstalled = XMLToolKit::Instance()->AreCityOrnamentsInstalled(m_anno1800data10AssetsLocation);

	ModState::AreClubOrnamentsInstalled = XMLToolKit::Instance()->AreClubOrnamentsInstalled(m_anno1800data10AssetsLocation);

	ModState::AreExtraOrnamentsInstalled = XMLToolKit::Instance()->AreExtraOrnamentsInstalled(m_anno1800data14AssetsLocation) && XMLToolKit::Instance()->AreExtraOrnamentsInstalled(m_anno1800data15AssetsLocation) && XMLToolKit::Instance()->AreExtraOrnamentsInstalled(m_anno1800data16AssetsLocation);

	ModState::AreCheatOrnamentsInstalled = XMLToolKit::Instance()->AreCheatOrnamentsInstalled(m_anno1800data10AssetsLocation);

	ModState::AreVisualObjectsOrnaments = XMLToolKit::Instance()->AreVisualObjectsOrnaments(m_anno1800data10AssetsLocation);

	ModState::AreOrnamentsBoosted = XMLToolKit::Instance()->AreOrnamentsBoosted(m_anno1800data10AssetsLocation);
}

void Mod::RunTest()
{
	std::cout << "TEST COMMENCING - THIS WILL TAKE A LONG TIME!" << std::endl;

	// First we install and uninstall 2 times
	ApplyAction(ModAction::INSTALL_ALL);
	ApplyAction(ModAction::UNINSTALL_ALL);
	ApplyAction(ModAction::INSTALL_ALL);
	ApplyAction(ModAction::UNINSTALL_ALL);

	// Then we install and uninstall in random order
	std::vector<ModAction> actions = { ModAction::TOGGLE_CITY_ORNAMENTS, ModAction::TOGGLE_CHEAT_ORNAMENTS, ModAction::TOGGLE_CLUB_ORNAMENTS, ModAction::TOGGLE_ORNAMENT_BOOST, ModAction::TOGGLE_SQUARE_ORNAMENT, ModAction::TOGGLE_VISUALOBJECTS_ORNAMENTS, ModAction::TOGGLE_ZOOM };
	for (int i = 0; i < TEST_TIMES; i++)
	{
		std::shuffle(actions.begin(), actions.end(), std::mt19937(std::random_device{}()));
		for (ModAction action : actions)
		{
			ApplyAction(action);
		}
	}

	// And last we again install and uninstall 2 times
	ApplyAction(ModAction::INSTALL_ALL);
	ApplyAction(ModAction::UNINSTALL_ALL);
	ApplyAction(ModAction::INSTALL_ALL);
	ApplyAction(ModAction::UNINSTALL_ALL);

	std::cout << "FINISHED TEST - If no errors/exceptions/etc happened, all is (probably) fine." << std::endl << std::endl;
}
