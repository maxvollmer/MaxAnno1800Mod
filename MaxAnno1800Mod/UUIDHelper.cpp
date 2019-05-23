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
#include "UUIDHelper.h"

// Code for generating UUID taken from here: https://lowrey.me/guid-generation-in-c-11/

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <string>

using namespace MaxAnno1800Mod;

std::string UUIDHelper::GetRandomUUID()
{
	std::stringstream uuid;
	uuid << GenerateHexString(4);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(6);
	return uuid.str();
}

unsigned char UUIDHelper::RandomChar()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return static_cast<unsigned char>(dis(gen));
}

std::string UUIDHelper::GenerateHexString(const unsigned int len)
{
	std::stringstream ss;
	for (unsigned int i = 0; i < len; i++)
	{
		auto rc = RandomChar();
		std::stringstream hexstream;
		hexstream << std::hex << int(rc);
		auto hex = hexstream.str();
		ss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return ss.str();
}
