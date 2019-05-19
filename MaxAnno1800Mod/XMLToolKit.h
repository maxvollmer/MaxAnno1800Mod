#pragma once

#include <memory>
#include <filesystem>

namespace MaxAnno1800Mod
{
	class XMLToolKit
	{
	public:

		static const std::unique_ptr<XMLToolKit>& Instance() { return m_instance; }

		bool IsZoomInstalled(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile) const;
		bool IsSquareOrnamentInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const;
		bool AreClubOrnamentsInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const;
		bool AreCheatOrnamentsInstalled(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation) const;

		void ToggleZoom(const std::filesystem::path& pViewDistanceSettingsFile, const std::filesystem::path& pCameraSettingsFile, bool install) const;
		void ToggleSquareOrnament(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const;
		void ToggleClubOrnaments(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const;
		void ToggleCheatOrnaments(const std::filesystem::path& pdata0AssetsLocation, const std::filesystem::path& pdata10AssetsLocation, bool install) const;

	private:
		XMLToolKit();

		using StateCallback = int(__stdcall *)(void*, void*);
		using InstallCallback = void(__stdcall *)(void*, void*, int);

		StateCallback _IsZoomInstalled{ nullptr };
		StateCallback _IsSquareOrnamentInstalled{ nullptr };
		StateCallback _AreClubOrnamentsInstalled{ nullptr };
		StateCallback _AreCheatOrnamentsInstalled{ nullptr };

		InstallCallback _ToggleZoom{ nullptr };
		InstallCallback _ToggleSquareOrnament{ nullptr };
		InstallCallback _ToggleClubOrnaments{ nullptr };
		InstallCallback _ToggleCheatOrnaments{ nullptr };

		static std::unique_ptr<XMLToolKit> m_instance;
	};

}
