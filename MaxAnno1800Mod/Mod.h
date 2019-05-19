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

		void ExportGameData();
		void InitModState();
		void ApplyAction(ModAction action);
		void ImportGameData();

	private:
		void BackupGameData();
		void PrintHeader();
		void GetLocations();
		void RestoreBackup();

		std::filesystem::path m_modLocation;
		std::filesystem::path m_anno1800InstallLocation;
		std::filesystem::path m_tempFolder;

		std::filesystem::path m_quickbmsExe;
		std::filesystem::path m_quickbms1800Script;

		std::filesystem::path m_anno1800data0Location;
		std::filesystem::path m_anno1800data10Location;

		std::filesystem::path m_anno1800data0ViewDistanceSettingsLocation;
		std::filesystem::path m_anno1800data0CameraSettingsLocation;
		std::filesystem::path m_anno1800data0AssetsLocation;
		std::filesystem::path m_anno1800data10AssetsLocation;
	};
}
