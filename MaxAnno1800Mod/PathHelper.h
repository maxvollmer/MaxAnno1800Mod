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
